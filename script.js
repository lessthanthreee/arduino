document.addEventListener('DOMContentLoaded', () => {
    // Initialize AOS
    AOS.init({
        duration: 800,
        once: true,
        offset: 100
    });

    // Header scroll effect
    const header = document.querySelector('header');
    window.addEventListener('scroll', () => {
        if (window.scrollY > 100) {
            header.classList.add('scrolled');
        } else {
            header.classList.remove('scrolled');
        }
    });

    // Smooth scrolling for navigation links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            e.preventDefault();
            const target = document.querySelector(this.getAttribute('href'));
            const headerOffset = 80;
            const elementPosition = target.getBoundingClientRect().top;
            const offsetPosition = elementPosition + window.pageYOffset - headerOffset;

            window.scrollTo({
                top: offsetPosition,
                behavior: 'smooth'
            });
        });
    });

    // PC Card hover effects
    const pcCards = document.querySelectorAll('.pc-card');
    pcCards.forEach(card => {
        card.addEventListener('mouseenter', function() {
            this.style.transform = 'translateY(-10px)';
            this.style.boxShadow = 'var(--hover-shadow)';
        });

        card.addEventListener('mouseleave', function() {
            this.style.transform = 'translateY(0)';
            this.style.boxShadow = 'var(--card-shadow)';
        });
    });

    // Contact form submission handler
    const contactForm = document.getElementById('contact-form');
    if (contactForm) {
        contactForm.addEventListener('submit', function(e) {
            e.preventDefault();
            
            // Basic form validation
            const name = this.querySelector('input[type="text"]').value.trim();
            const email = this.querySelector('input[type="email"]').value.trim();
            const message = this.querySelector('textarea').value.trim();

            if (!name || !email || !message) {
                showNotification('Please fill out all fields', 'error');
                return;
            }

            // Email validation regex
            const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
            if (!emailRegex.test(email)) {
                showNotification('Please enter a valid email address', 'error');
                return;
            }

            // Simulate form submission
            showNotification('Thank you for your message! We will get back to you soon.', 'success');
            this.reset();
        });
    }

    // PC Card Inquiry Buttons
    const inquiryButtons = document.querySelectorAll('.inquire-btn');
    inquiryButtons.forEach(button => {
        button.addEventListener('click', function() {
            const pcCard = this.closest('.pc-card');
            const pcName = pcCard.querySelector('h3').textContent;
            const pcSpecs = pcCard.querySelector('p').textContent;
            const pcPrice = pcCard.querySelector('.price').textContent;

            // Create and show modal
            showInquiryModal(pcName, pcSpecs, pcPrice);
        });
    });

    // Notification system
    function showNotification(message, type = 'success') {
        const notification = document.createElement('div');
        notification.className = `notification ${type}`;
        notification.textContent = message;

        document.body.appendChild(notification);

        // Animate in
        setTimeout(() => {
            notification.style.transform = 'translateX(0)';
            notification.style.opacity = '1';
        }, 100);

        // Remove after 3 seconds
        setTimeout(() => {
            notification.style.transform = 'translateX(100%)';
            notification.style.opacity = '0';
            setTimeout(() => {
                document.body.removeChild(notification);
            }, 300);
        }, 3000);
    }

    // Inquiry Modal
    function showInquiryModal(pcName, pcSpecs, pcPrice) {
        const modal = document.createElement('div');
        modal.className = 'modal';
        modal.innerHTML = `
            <div class="modal-content">
                <span class="close-modal">&times;</span>
                <h3>Inquire About ${pcName}</h3>
                <p><strong>Specifications:</strong> ${pcSpecs}</p>
                <p><strong>Price:</strong> ${pcPrice}</p>
                <form class="inquiry-form">
                    <input type="text" placeholder="Your Name" required>
                    <input type="email" placeholder="Your Email" required>
                    <input type="tel" placeholder="Your Phone (optional)">
                    <textarea placeholder="Additional Questions or Comments" required></textarea>
                    <button type="submit" class="submit-btn">Send Inquiry</button>
                </form>
            </div>
        `;

        document.body.appendChild(modal);

        // Animate modal in
        setTimeout(() => {
            modal.style.opacity = '1';
            modal.querySelector('.modal-content').style.transform = 'translateY(0)';
        }, 10);

        // Close modal functionality
        const closeBtn = modal.querySelector('.close-modal');
        closeBtn.addEventListener('click', () => closeModal(modal));

        // Close on outside click
        modal.addEventListener('click', (e) => {
            if (e.target === modal) closeModal(modal);
        });

        // Handle form submission
        const inquiryForm = modal.querySelector('.inquiry-form');
        inquiryForm.addEventListener('submit', (e) => {
            e.preventDefault();
            showNotification('Thank you for your inquiry! We will contact you shortly.', 'success');
            closeModal(modal);
        });
    }

    function closeModal(modal) {
        modal.style.opacity = '0';
        modal.querySelector('.modal-content').style.transform = 'translateY(-20px)';
        setTimeout(() => {
            document.body.removeChild(modal);
        }, 300);
    }

    // Add custom cursor effect for interactive elements
    const buttons = document.querySelectorAll('button, .cta-button, nav a');
    buttons.forEach(button => {
        button.addEventListener('mousemove', (e) => {
            const rect = button.getBoundingClientRect();
            const x = e.clientX - rect.left;
            const y = e.clientY - rect.top;
            
            button.style.setProperty('--x', `${x}px`);
            button.style.setProperty('--y', `${y}px`);
        });
    });

    // Particle animation
    const canvas = document.getElementById('particles');
    const ctx = canvas.getContext('2d');

    // Set canvas size
    function setCanvasSize() {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
    }
    setCanvasSize();
    window.addEventListener('resize', setCanvasSize);

    // Mouse position
    let mouse = {
        x: null,
        y: null,
        radius: 150
    }

    window.addEventListener('mousemove', function(event) {
        mouse.x = event.x;
        mouse.y = event.y;
    });

    // Particle class
    class Particle {
        constructor(x, y) {
            this.x = x;
            this.y = y;
            this.baseX = x;
            this.baseY = y;
            this.size = Math.random() * 3 + 1;
            this.density = Math.random() * 30 + 1;
            this.color = this.getRandomColor();
        }

        getRandomColor() {
            const colors = [
                'rgba(45, 93, 123, 0.8)',  // secondary color
                'rgba(214, 64, 69, 0.8)',  // accent color
                'rgba(26, 31, 60, 0.8)'    // primary color
            ];
            return colors[Math.floor(Math.random() * colors.length)];
        }

        draw() {
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2);
            ctx.fillStyle = this.color;
            ctx.fill();
        }

        update() {
            // Distance between mouse and particle
            let dx = mouse.x - this.x;
            let dy = mouse.y - this.y;
            let distance = Math.sqrt(dx * dx + dy * dy);

            let forceDirectionX = dx / distance;
            let forceDirectionY = dy / distance;

            // Max distance, past that the force will be 0
            const maxDistance = 150;
            let force = (maxDistance - distance) / maxDistance;

            // If we're too far away, no force is applied
            if (force < 0) force = 0;

            let directionX = (forceDirectionX * force * this.density);
            let directionY = (forceDirectionY * force * this.density);

            if (distance < maxDistance) {
                this.x -= directionX;
                this.y -= directionY;
            } else {
                if (this.x !== this.baseX) {
                    let dx = this.x - this.baseX;
                    this.x -= dx/10;
                }
                if (this.y !== this.baseY) {
                    let dy = this.y - this.baseY;
                    this.y -= dy/10;
                }
            }
        }
    }

    // Create particle array
    let particleArray = [];
    function init() {
        particleArray = [];
        let numberOfParticles = (canvas.width * canvas.height) / 9000;
        for (let i = 0; i < numberOfParticles; i++) {
            let x = Math.random() * canvas.width;
            let y = Math.random() * canvas.height;
            particleArray.push(new Particle(x, y));
        }
    }

    // Animation loop
    function animate() {
        requestAnimationFrame(animate);
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        for (let i = 0; i < particleArray.length; i++) {
            particleArray[i].update();
            particleArray[i].draw();
        }
        connect();
    }

    // Connect nearby particles with lines
    function connect() {
        let opacityValue = 1;
        for (let a = 0; a < particleArray.length; a++) {
            for (let b = a; b < particleArray.length; b++) {
                let dx = particleArray[a].x - particleArray[b].x;
                let dy = particleArray[a].y - particleArray[b].y;
                let distance = Math.sqrt(dx * dx + dy * dy);

                if (distance < 100) {
                    opacityValue = 1 - (distance/100);
                    ctx.strokeStyle = `rgba(230, 241, 255, ${opacityValue * 0.2})`;
                    ctx.lineWidth = 1;
                    ctx.beginPath();
                    ctx.moveTo(particleArray[a].x, particleArray[a].y);
                    ctx.lineTo(particleArray[b].x, particleArray[b].y);
                    ctx.stroke();
                }
            }
        }
    }

    // Handle window resize
    window.addEventListener('resize', function() {
        setCanvasSize();
        init();
    });

    // Initialize and start animation
    init();
    animate();

    // Reset mouse position when mouse leaves window
    window.addEventListener('mouseout', function() {
        mouse.x = undefined;
        mouse.y = undefined;
    });
});
