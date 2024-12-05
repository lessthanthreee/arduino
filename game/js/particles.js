import * as THREE from 'three';
import { MathUtils } from './utils.js';

export class ParticleEmitter {
    constructor(scene) {
        this.scene = scene;
        this.particles = [];
        this.geometry = new THREE.BufferGeometry();
        this.positions = new Float32Array(1000 * 3);
        this.colors = new Float32Array(1000 * 3);
        this.sizes = new Float32Array(1000);
        this.alphas = new Float32Array(1000);
        this.velocities = [];
        
        this.geometry.setAttribute('position', new THREE.BufferAttribute(this.positions, 3));
        this.geometry.setAttribute('color', new THREE.BufferAttribute(this.colors, 3));
        this.geometry.setAttribute('size', new THREE.BufferAttribute(this.sizes, 1));
        this.geometry.setAttribute('alpha', new THREE.BufferAttribute(this.alphas, 1));
        
        const sprite = new THREE.TextureLoader().load('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAAWJQAAFiUBSVIk8AAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAALISURBVFiF7ZdNSBRhGMd/M7urzq4fSB/QhyXRQSyDgqKDdOkQFUVJdokOniKig3WLjhEFXTpFdQsigoiCqEOHCCIiKgixyK9dZT+c/dibszvO7szO7EfMH4Zl5p3ned7/+z7v884zryaEEPyHpv1rAACaRm8xJ4LYTBubyWaYNqZlYpkWwhZ4XR5cLhcejwePZuDXA/g0Px7Ng0fT0TRNaWNLAZi2SV9ykP7UEEPpYZKZUZKZJBPZSdLZNDk7R86yyNtg2zaWbSNsgRAC27axbRvDMNA1HZfLha7p6JqOYRi4XW5Cep6wK0JlIMKSYJjFwQihQIiAK4CmaQtDkLNzPBp+xoORHp6Pv2I4M0o6m8YWgnwuT97OY+UtbGEjEAhAIBACy7IQQiCEQAgbXdMxDANd1zEMA7fbjdftJeQNUh2sYG24jk2RTdSGatE1/c8AHqcGOXP/HI8/v2UsPUbOypHP5RkbG2NycpLp6WkymQzZbJZcLodpmgghELaNrutUVlYSCoUIh8NEo1Gqq6tZFa5iR2wbu2p2EPaF5wY4ef8MN97cYnR6jJnpGZLJJCMjIyQSCRKJBFNTU2QyGfL5/JxQDMPAMAwCgQDBYJBIJEJVVRU1NTU0LG1ge2wbjZXr0DQNYQN7L+/ndu9dxifGSSaTJBIJRkdHmZiYIJ1Ok81mMU1zFoKu67hcLnw+H36/n1AoRDgcprKykqWVS9lYvp7Wla0EjADtPR1c7+tmYnKCVCpFKpUinU6TyWQwTRPLsmZj7nK5CAQChEIhwuEwkUiEWGWMluomWle0EPQEudJzlRtv75BMpTBNc9bxXPZ4PPhcPvxuPz7dh8/lw+v24tE9uHU3hm7g0l0YuoFhGOiajltzoxs6Xs2L3+0n6A0S9ASp8JUT9UeJ+qOUB8oJeAIL+ydUmQpAZSoAlakAVKYCUJkKQGUqAJX9AyLkUF+gWGi0AAAAAElFTkSuQmCC');
        
        this.material = new THREE.ShaderMaterial({
            uniforms: {
                texture: { value: sprite }
            },
            vertexShader: `
                attribute float size;
                attribute float alpha;
                attribute vec3 color;
                varying float vAlpha;
                varying vec3 vColor;
                
                void main() {
                    vAlpha = alpha;
                    vColor = color;
                    vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);
                    gl_PointSize = size * (300.0 / -mvPosition.z);
                    gl_Position = projectionMatrix * mvPosition;
                }
            `,
            fragmentShader: `
                uniform sampler2D texture;
                varying float vAlpha;
                varying vec3 vColor;
                
                void main() {
                    vec4 texColor = texture2D(texture, gl_PointCoord);
                    gl_FragColor = vec4(vColor, vAlpha) * texColor;
                }
            `,
            blending: THREE.AdditiveBlending,
            depthTest: true,
            depthWrite: false,
            transparent: true
        });
        
        this.points = new THREE.Points(this.geometry, this.material);
        this.scene.add(this.points);
        
        this.count = 0;
    }
    
    emit(position, color, count = 10) {
        for (let i = 0; i < count; i++) {
            if (this.count >= 1000) return;
            
            const index = this.count * 3;
            this.positions[index] = position.x;
            this.positions[index + 1] = position.y;
            this.positions[index + 2] = position.z;
            
            this.colors[index] = color.r;
            this.colors[index + 1] = color.g;
            this.colors[index + 2] = color.b;
            
            this.sizes[this.count] = MathUtils.randomFloat(10, 20);
            this.alphas[this.count] = 1.0;
            
            this.velocities[this.count] = new THREE.Vector3(
                MathUtils.randomFloat(-1, 1),
                MathUtils.randomFloat(2, 4),
                MathUtils.randomFloat(-1, 1)
            );
            
            this.count++;
        }
        
        this.geometry.attributes.position.needsUpdate = true;
        this.geometry.attributes.color.needsUpdate = true;
        this.geometry.attributes.size.needsUpdate = true;
        this.geometry.attributes.alpha.needsUpdate = true;
    }
    
    update(deltaTime) {
        for (let i = 0; i < this.count; i++) {
            const index = i * 3;
            
            // Update position
            this.positions[index] += this.velocities[i].x * deltaTime;
            this.positions[index + 1] += this.velocities[i].y * deltaTime;
            this.positions[index + 2] += this.velocities[i].z * deltaTime;
            
            // Apply gravity
            this.velocities[i].y -= 9.8 * deltaTime;
            
            // Update alpha
            this.alphas[i] -= deltaTime;
            
            // Remove dead particles
            if (this.alphas[i] <= 0) {
                // Move last particle to this position
                this.count--;
                if (i === this.count) continue;
                
                const lastIndex = this.count * 3;
                this.positions[index] = this.positions[lastIndex];
                this.positions[index + 1] = this.positions[lastIndex + 1];
                this.positions[index + 2] = this.positions[lastIndex + 2];
                
                this.colors[index] = this.colors[lastIndex];
                this.colors[index + 1] = this.colors[lastIndex + 1];
                this.colors[index + 2] = this.colors[lastIndex + 2];
                
                this.sizes[i] = this.sizes[this.count];
                this.alphas[i] = this.alphas[this.count];
                this.velocities[i] = this.velocities[this.count];
                
                i--;
            }
        }
        
        this.geometry.attributes.position.needsUpdate = true;
        this.geometry.attributes.color.needsUpdate = true;
        this.geometry.attributes.size.needsUpdate = true;
        this.geometry.attributes.alpha.needsUpdate = true;
    }
    
    createCollectEffect(position) {
        const color = new THREE.Color(0xFFD700);
        this.emit(position, color, 20);
    }
    
    createMultiplierEffect(position) {
        const color = new THREE.Color(0xFF4500);
        this.emit(position, color, 30);
    }
    
    createDeathEffect(position) {
        const color = new THREE.Color(0xFF0000);
        this.emit(position, color, 50);
    }
}
