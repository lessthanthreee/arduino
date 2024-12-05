import * as THREE from 'three';
import { EffectComposer } from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } from 'three/addons/postprocessing/RenderPass.js';
import { UnrealBloomPass } from 'three/addons/postprocessing/UnrealBloomPass.js';

export class MathUtils {
    static lerp(start, end, t) {
        return start * (1 - t) + end * t;
    }

    static clamp(value, min, max) {
        return Math.max(min, Math.min(max, value));
    }

    static randomFloat(min, max) {
        return Math.random() * (max - min) + min;
    }

    static randomInt(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
}

export class LoadingManager {
    constructor() {
        this.loadingScreen = document.querySelector('.loading-screen');
        this.progressBar = document.querySelector('.progress');
        this.totalAssets = 0;
        this.loadedAssets = 0;
    }

    setTotalAssets(total) {
        this.totalAssets = total;
    }

    updateProgress() {
        this.loadedAssets++;
        const progress = (this.loadedAssets / this.totalAssets) * 100;
        this.progressBar.style.width = `${progress}%`;

        if (this.loadedAssets === this.totalAssets) {
            this.hideLoadingScreen();
        }
    }

    hideLoadingScreen() {
        setTimeout(() => {
            this.loadingScreen.classList.add('hidden');
        }, 500);
    }
}

export class ParticleSystem {
    constructor(scene) {
        this.scene = scene;
        this.particles = [];
    }

    createParticle(position, color) {
        const geometry = new THREE.SphereGeometry(0.1, 8, 8);
        const material = new THREE.MeshBasicMaterial({
            color: color,
            transparent: true,
            opacity: 1
        });
        const particle = new THREE.Mesh(geometry, material);
        particle.position.copy(position);
        particle.velocity = new THREE.Vector3(
            MathUtils.randomFloat(-1, 1),
            MathUtils.randomFloat(2, 4),
            MathUtils.randomFloat(-1, 1)
        );
        particle.life = 1.0;
        this.particles.push(particle);
        this.scene.add(particle);
    }

    update(deltaTime) {
        for (let i = this.particles.length - 1; i >= 0; i--) {
            const particle = this.particles[i];
            particle.position.add(particle.velocity.clone().multiplyScalar(deltaTime));
            particle.velocity.y -= 5 * deltaTime; // gravity
            particle.life -= deltaTime;
            particle.material.opacity = particle.life;

            if (particle.life <= 0) {
                this.scene.remove(particle);
                this.particles.splice(i, 1);
            }
        }
    }
}

export class AudioManager {
    constructor() {
        this.sounds = {};
        this.listener = new THREE.AudioListener();
        this.loader = new THREE.AudioLoader();
    }

    load(name, url) {
        return new Promise((resolve, reject) => {
            this.loader.load(url, (buffer) => {
                const sound = new THREE.Audio(this.listener);
                sound.setBuffer(buffer);
                this.sounds[name] = sound;
                resolve();
            }, null, reject);
        });
    }

    play(name, volume = 1) {
        const sound = this.sounds[name];
        if (sound && !sound.isPlaying) {
            sound.setVolume(volume);
            sound.play();
        }
    }
}

export class PostProcessing {
    constructor(renderer, scene, camera) {
        this.composer = new EffectComposer(renderer);
        
        // Regular scene rendering
        const renderPass = new RenderPass(scene, camera);
        this.composer.addPass(renderPass);
        
        // Bloom effect
        const bloomPass = new UnrealBloomPass(
            new THREE.Vector2(window.innerWidth, window.innerHeight),
            1.5,  // strength
            0.4,  // radius
            0.85  // threshold
        );
        this.composer.addPass(bloomPass);
    }

    render() {
        this.composer.render();
    }

    setSize(width, height) {
        this.composer.setSize(width, height);
    }
}
