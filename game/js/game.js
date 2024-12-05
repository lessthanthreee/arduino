import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { DRACOLoader } from 'three/addons/loaders/DRACOLoader.js';
import { EffectComposer } from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/addons/postprocessing/RenderPass.js';
import { UnrealBloomPass } from 'three/addons/postprocessing/UnrealBloomPass.js';
import { ShaderPass } from 'three/addons/postprocessing/ShaderPass.js';

import { MathUtils, LoadingManager, AudioManager } from './utils.js';
import { ModelManager } from './models.js';
import { ParticleEmitter } from './particles.js';

class Game {
    constructor() {
        // Add error handling
        try {
            this.setupScene();
            this.setupGame();
            this.setupEventListeners();
            this.animate();
        } catch (error) {
            console.error('Failed to initialize game:', error);
            document.querySelector('.loading-screen').classList.add('hidden');
            document.getElementById('error-screen').classList.remove('hidden');
            document.getElementById('error-message').textContent = 'Failed to initialize game: ' + error.message;
        }
    }

    setupScene() {
        // Scene setup
        this.scene = new THREE.Scene();
        this.scene.background = new THREE.Color(0x1a1a1a);
        this.scene.fog = new THREE.Fog(0x1a1a1a, 20, 100);

        // Camera setup
        this.camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
        this.camera.position.set(0, 5, 10);
        this.camera.lookAt(0, 0, 0);

        // Renderer setup
        this.renderer = new THREE.WebGLRenderer({ 
            antialias: true,
            powerPreference: "high-performance",
            stencil: false,
            depth: true
        });
        this.renderer.setSize(window.innerWidth, window.innerHeight);
        this.renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
        this.renderer.shadowMap.enabled = true;
        this.renderer.shadowMap.type = THREE.PCFSoftShadowMap;
        this.renderer.outputColorSpace = THREE.SRGBColorSpace;
        document.getElementById('game-canvas').appendChild(this.renderer.domElement);

        // Lighting
        const ambientLight = new THREE.AmbientLight(0x404040, 2);
        this.scene.add(ambientLight);

        const directionalLight = new THREE.DirectionalLight(0xffffff, 2);
        directionalLight.position.set(5, 5, 5);
        directionalLight.castShadow = true;
        directionalLight.shadow.mapSize.width = 2048;
        directionalLight.shadow.mapSize.height = 2048;
        directionalLight.shadow.camera.near = 0.1;
        directionalLight.shadow.camera.far = 500;
        directionalLight.shadow.bias = -0.0001;
        this.scene.add(directionalLight);

        // Add some point lights for better atmosphere
        const pointLight1 = new THREE.PointLight(0x4CAF50, 1, 10);
        pointLight1.position.set(-5, 5, 0);
        this.scene.add(pointLight1);

        const pointLight2 = new THREE.PointLight(0xFF4500, 1, 10);
        pointLight2.position.set(5, 5, 0);
        this.scene.add(pointLight2);

        // Post-processing
        this.setupPostProcessing();

        // Resize handler
        window.addEventListener('resize', () => {
            this.camera.aspect = window.innerWidth / window.innerHeight;
            this.camera.updateProjectionMatrix();
            this.renderer.setSize(window.innerWidth, window.innerHeight);
            this.composer.setSize(window.innerWidth, window.innerHeight);
        });
    }

    setupPostProcessing() {
        this.composer = new EffectComposer(this.renderer);
        
        const renderPass = new RenderPass(this.scene, this.camera);
        this.composer.addPass(renderPass);
        
        const bloomPass = new UnrealBloomPass(
            new THREE.Vector2(window.innerWidth, window.innerHeight),
            1.0,  // strength
            0.4,  // radius
            0.85  // threshold
        );
        this.composer.addPass(bloomPass);
    }

    setupGame() {
        // Game state
        this.score = 0;
        this.multiplier = 1;
        this.gameOver = false;
        this.isPlaying = false;

        // Loading manager
        this.loadingManager = new LoadingManager();

        // Model manager
        this.modelManager = new ModelManager(this.scene, this.loadingManager);

        // Particle system
        this.particles = new ParticleEmitter(this.scene);

        // Audio manager
        this.audio = new AudioManager();
        this.camera.add(this.audio.listener);

        // Create environment
        this.environment = this.modelManager.createEnvironment();
        this.scene.add(this.environment);

        // Create player
        this.player = {
            model: this.modelManager.createCharacter(),
            position: new THREE.Vector3(0, 0, 0),
            velocity: new THREE.Vector3(0, 0, 0),
            isJumping: false
        };
        this.scene.add(this.player.model);

        // Items
        this.items = [];
        this.lastItemSpawn = 0;

        // Camera follow
        this.cameraTarget = new THREE.Vector3();
        this.cameraOffset = new THREE.Vector3(0, 5, 10);

        // Input state
        this.keys = {};

        // Hide loading screen
        document.querySelector('.loading-screen').classList.add('hidden');
    }

    setupEventListeners() {
        document.addEventListener('keydown', (e) => this.keys[e.code] = true);
        document.addEventListener('keyup', (e) => this.keys[e.code] = false);
        
        document.getElementById('startButton').addEventListener('click', () => this.startGame());
        document.getElementById('restartButton').addEventListener('click', () => this.startGame());
    }

    startGame() {
        this.score = 0;
        this.multiplier = 1;
        this.gameOver = false;
        this.isPlaying = true;
        this.items = [];
        this.player.position.set(0, 0, 0);
        this.player.velocity.set(0, 0, 0);
        this.player.isJumping = false;

        document.getElementById('startScreen').classList.add('hidden');
        document.getElementById('gameOverScreen').classList.add('hidden');

        // Update UI
        document.getElementById('scoreValue').textContent = '0';
        document.getElementById('multiplierValue').textContent = '1x';
    }

    spawnItem() {
        const now = performance.now();
        if (now - this.lastItemSpawn < 1000) return;

        const types = ['tendie', 'multiplier', 'wagework'];
        const type = types[Math.floor(Math.random() * types.length)];
        const item = {
            model: this.modelManager.createItem(type),
            type: type,
            position: new THREE.Vector3(
                15,
                MathUtils.randomFloat(1, 3),
                MathUtils.randomFloat(-2, 2)
            )
        };
        this.scene.add(item.model);
        this.items.push(item);
        this.lastItemSpawn = now;
    }

    updatePlayer(deltaTime) {
        // Horizontal movement
        const moveSpeed = 10;
        if (this.keys['ArrowLeft'] || this.keys['KeyA']) {
            this.player.velocity.x = -moveSpeed;
        } else if (this.keys['ArrowRight'] || this.keys['KeyD']) {
            this.player.velocity.x = moveSpeed;
        } else {
            this.player.velocity.x = 0;
        }

        // Jumping
        if ((this.keys['Space'] || this.keys['ArrowUp']) && !this.player.isJumping) {
            this.player.velocity.y = 15;
            this.player.isJumping = true;
        }

        // Apply gravity
        this.player.velocity.y -= 30 * deltaTime;

        // Update position
        this.player.position.x += this.player.velocity.x * deltaTime;
        this.player.position.y += this.player.velocity.y * deltaTime;

        // Ground collision
        if (this.player.position.y < 0) {
            this.player.position.y = 0;
            this.player.velocity.y = 0;
            this.player.isJumping = false;
        }

        // Boundary constraints
        this.player.position.x = MathUtils.clamp(this.player.position.x, -5, 5);
        this.player.position.z = MathUtils.clamp(this.player.position.z, -2, 2);

        // Update model position
        this.player.model.position.copy(this.player.position);
    }

    updateItems(deltaTime) {
        this.spawnItem();

        for (let i = this.items.length - 1; i >= 0; i--) {
            const item = this.items[i];
            item.position.x -= 10 * deltaTime;
            item.model.position.copy(item.position);

            // Check collision
            if (this.checkCollision(this.player.position, item.position)) {
                switch(item.type) {
                    case 'tendie':
                        this.score += 10 * this.multiplier;
                        this.particles.createCollectEffect(item.position);
                        break;
                    case 'multiplier':
                        this.multiplier *= 2;
                        this.particles.createMultiplierEffect(item.position);
                        break;
                    case 'wagework':
                        this.gameOver = true;
                        this.particles.createDeathEffect(item.position);
                        break;
                }

                this.scene.remove(item.model);
                this.items.splice(i, 1);
            }
            // Remove if off screen
            else if (item.position.x < -10) {
                this.scene.remove(item.model);
                this.items.splice(i, 1);
            }
        }
    }

    updateCamera(deltaTime) {
        // Smooth camera follow
        this.cameraTarget.copy(this.player.position).add(new THREE.Vector3(0, 2, 0));
        this.camera.position.lerp(this.cameraTarget.clone().add(this.cameraOffset), 5 * deltaTime);
        this.camera.lookAt(this.cameraTarget);
    }

    checkCollision(pos1, pos2) {
        const dx = pos1.x - pos2.x;
        const dy = pos1.y - pos2.y;
        const dz = pos1.z - pos2.z;
        return Math.sqrt(dx * dx + dy * dy + dz * dz) < 1.5;
    }

    update(deltaTime) {
        if (!this.isPlaying) return;

        this.updatePlayer(deltaTime);
        this.updateItems(deltaTime);
        this.updateCamera(deltaTime);
        this.particles.update(deltaTime);

        // Update UI
        document.getElementById('scoreValue').textContent = Math.floor(this.score);
        document.getElementById('multiplierValue').textContent = this.multiplier + 'x';

        if (this.gameOver) {
            this.endGame();
        }
    }

    endGame() {
        this.isPlaying = false;
        document.getElementById('finalScore').textContent = Math.floor(this.score);
        document.getElementById('gameOverScreen').classList.remove('hidden');
    }

    animate(currentTime) {
        requestAnimationFrame((time) => this.animate(time));

        const deltaTime = (currentTime - (this.lastTime || currentTime)) / 1000;
        this.lastTime = currentTime;

        if (this.isPlaying) {
            this.update(Math.min(deltaTime, 0.1));
        }

        this.composer.render();
    }
}

// Start the game when the page loads
window.onload = () => {
    try {
        new Game();
    } catch (error) {
        console.error('Failed to start game:', error);
        document.querySelector('.loading-screen').classList.add('hidden');
        document.getElementById('error-screen').classList.remove('hidden');
        document.getElementById('error-message').textContent = 'Failed to start game: ' + error.message;
    }
};
