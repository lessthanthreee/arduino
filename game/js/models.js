import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { DRACOLoader } from 'three/addons/loaders/DRACOLoader.js';
import { MathUtils } from './utils.js';

export class ModelManager {
    constructor(scene, loadingManager) {
        this.scene = scene;
        this.loadingManager = loadingManager;
        this.models = {};
        
        // Set up model loader
        this.loader = new GLTFLoader();
        const dracoLoader = new DRACOLoader();
        dracoLoader.setDecoderPath('https://www.gstatic.com/draco/v1/decoders/');
        this.loader.setDRACOLoader(dracoLoader);
    }

    async loadModel(name, url) {
        try {
            const gltf = await this.loader.loadAsync(url);
            this.models[name] = gltf.scene;
            this.loadingManager.updateProgress();
            return gltf.scene;
        } catch (error) {
            console.error(`Error loading model ${name}:`, error);
            // Create a placeholder cube if model fails to load
            return this.createPlaceholder();
        }
    }

    createPlaceholder() {
        // Create a simple colored cube as placeholder
        const geometry = new THREE.BoxGeometry(1, 1, 1);
        const material = new THREE.MeshPhongMaterial({ 
            color: 0x4CAF50,
            emissive: 0x4CAF50,
            emissiveIntensity: 0.2
        });
        return new THREE.Mesh(geometry, material);
    }

    createCharacter() {
        // Create a stylized character using basic shapes
        const group = new THREE.Group();

        // Body
        const bodyGeometry = new THREE.BoxGeometry(1, 1.5, 0.5);
        const bodyMaterial = new THREE.MeshPhongMaterial({ 
            color: 0x4CAF50,
            emissive: 0x4CAF50,
            emissiveIntensity: 0.2
        });
        const body = new THREE.Mesh(bodyGeometry, bodyMaterial);
        group.add(body);

        // Head
        const headGeometry = new THREE.BoxGeometry(0.8, 0.8, 0.8);
        const headMaterial = new THREE.MeshPhongMaterial({ 
            color: 0xFFE0BD,
            emissive: 0xFFE0BD,
            emissiveIntensity: 0.1
        });
        const head = new THREE.Mesh(headGeometry, headMaterial);
        head.position.y = 1.15;
        group.add(head);

        // Eyes
        const eyeGeometry = new THREE.SphereGeometry(0.1, 16, 16);
        const eyeMaterial = new THREE.MeshPhongMaterial({ 
            color: 0x000000,
            emissive: 0x000000,
            emissiveIntensity: 0.5
        });
        
        const leftEye = new THREE.Mesh(eyeGeometry, eyeMaterial);
        leftEye.position.set(-0.2, 1.2, 0.4);
        group.add(leftEye);
        
        const rightEye = new THREE.Mesh(eyeGeometry, eyeMaterial);
        rightEye.position.set(0.2, 1.2, 0.4);
        group.add(rightEye);

        return group;
    }

    createItem(type) {
        const group = new THREE.Group();
        let mesh;

        switch(type) {
            case 'tendie':
                // Create a chicken tender-like shape
                const tendieGeometry = new THREE.CylinderGeometry(0.2, 0.3, 1, 6);
                const tendieMaterial = new THREE.MeshPhongMaterial({
                    color: 0xFFD700,
                    emissive: 0xFFD700,
                    emissiveIntensity: 0.2
                });
                mesh = new THREE.Mesh(tendieGeometry, tendieMaterial);
                mesh.rotation.x = Math.PI / 2;
                break;

            case 'multiplier':
                // Create a glowing multiplier symbol
                const multiplierGeometry = new THREE.TorusGeometry(0.3, 0.1, 16, 32);
                const multiplierMaterial = new THREE.MeshPhongMaterial({
                    color: 0xFF4500,
                    emissive: 0xFF4500,
                    emissiveIntensity: 0.5
                });
                mesh = new THREE.Mesh(multiplierGeometry, multiplierMaterial);
                break;

            case 'wagework':
                // Create a briefcase-like shape
                const briefcaseGeometry = new THREE.BoxGeometry(0.8, 0.6, 0.3);
                const briefcaseMaterial = new THREE.MeshPhongMaterial({
                    color: 0xFF0000,
                    emissive: 0xFF0000,
                    emissiveIntensity: 0.3
                });
                mesh = new THREE.Mesh(briefcaseGeometry, briefcaseMaterial);
                break;
        }

        if (mesh) {
            group.add(mesh);
        }

        return group;
    }

    createEnvironment() {
        const group = new THREE.Group();

        // Ground
        const groundGeometry = new THREE.PlaneGeometry(100, 20);
        const groundMaterial = new THREE.MeshPhongMaterial({
            color: 0x1a1a1a,
            emissive: 0x1a1a1a,
            emissiveIntensity: 0.1,
            shininess: 10
        });
        const ground = new THREE.Mesh(groundGeometry, groundMaterial);
        ground.rotation.x = -Math.PI / 2;
        ground.position.y = -2;
        group.add(ground);

        // Background elements (random shapes suggesting a city)
        for (let i = 0; i < 20; i++) {
            const height = MathUtils.randomFloat(5, 15);
            const width = MathUtils.randomFloat(2, 4);
            const buildingGeometry = new THREE.BoxGeometry(width, height, 2);
            const buildingMaterial = new THREE.MeshPhongMaterial({
                color: 0x2a2a2a,
                emissive: 0x2a2a2a,
                emissiveIntensity: 0.1
            });
            const building = new THREE.Mesh(buildingGeometry, buildingMaterial);
            building.position.set(
                MathUtils.randomFloat(-30, 30),
                height/2 - 2,
                MathUtils.randomFloat(-10, -5)
            );
            group.add(building);
        }

        return group;
    }
}
