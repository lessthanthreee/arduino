// Game constants
const COINS = {
    NEET: { name: 'NEET Token', basePrice: 100, volatility: 2.0 },
    TENDIE: { name: 'Tendie Coin', basePrice: 50, volatility: 1.5 },
    WAGIES: { name: 'Wage Slave Token', basePrice: 10, volatility: 0.5 },
    PEPE: { name: 'Rare Pepe Coin', basePrice: 1000, volatility: 3.0 }
};

const EVENTS = [
    {
        title: "Mom Found the Mining Rig!",
        description: "Quick! Hide the GPUs under your body pillow collection!",
        choices: [
            { text: "Move it to the closet (-20 GBP)", effect: { gbp: -20, momPatience: -10 } },
            { text: "Explain crypto to mom (50% chance of working)", effect: { momPatience: -30, mentalHealth: -10 } },
            { text: "Pretend it's for 'machine learning'", effect: { socialCredit: +10, momPatience: +5 } }
        ]
    },
    {
        title: "Discord Server Drama!",
        description: "Someone posted cringe in the financial advice channel!",
        choices: [
            { text: "Ban them (Chad move)", effect: { socialCredit: +20, mentalHealth: +10 } },
            { text: "Start a flame war", effect: { socialCredit: -20, mentalHealth: -20 } },
            { text: "Post rare Pepe to calm everyone", effect: { socialCredit: +30 } }
        ]
    },
    {
        title: "New Anime Season!",
        description: "Your favorite series just dropped new episodes!",
        choices: [
            { text: "Binge watch (ignore portfolio)", effect: { mentalHealth: +30, portfolio: -0.1 } },
            { text: "Trade while watching", effect: { mentalHealth: +10, portfolio: -0.2 } },
            { text: "Stay focused on charts", effect: { mentalHealth: -20, portfolio: +0.1 } }
        ]
    }
];

const REDDIT_DD = [
    "Just mortgaged my house for NEET token! 🚀🚀🚀",
    "Technical Analysis shows we're in a Doritos pattern!",
    "My dog's veterinarian's cousin works at NEET headquarters!",
    "If we all buy $10 worth, we'll be millionaires!",
    "Trust me bro, I have insider information!"
];

const BIZ_POSTS = [
    ">he doesn't know about the upcoming NEET squeeze",
    "WAGIES ON SUICIDE WATCH",
    "Fundementals looking good. In for 100k.",
    "Bogdanoff says pamp eet",
    ">implying you're not all in on rare pepes"
];

const WAIFU_EXPRESSIONS = {
    neutral: 'url(https://example.com/neutral.png)',
    happy: 'url(https://example.com/happy.png)',
    sad: 'url(https://example.com/sad.png)',
    excited: 'url(https://example.com/excited.png)',
    panic: 'url(https://example.com/panic.png)'
};

class Game {
    constructor() {
        this.setupGameState();
        this.setupChart();
        this.setupWaifuDialogues();
        this.setupEventListeners();
        this.lastUpdate = Date.now();
        this.lastPriceUpdate = Date.now();
        this.isPlaying = false;
        this.spawnWaifuInterval = null;
    }

    setupGameState() {
        this.state = {
            portfolio: 1000,
            gbp: 100,
            mentalHealth: 100,
            stress: 0,
            hunger: 0,
            holdings: {},
            prices: {},
            priceHistory: {}
        };

        // Initialize prices and history for each coin
        const coins = ['NEET', 'TENDIE', 'WAGIES', 'PEPE'];
        coins.forEach(coin => {
            this.state.prices[coin] = 100; // Starting price
            this.state.holdings[coin] = 0;
            this.state.priceHistory[coin] = Array(100).fill(100);
        });

        this.selectedCoin = 'NEET';
    }

    setupChart() {
        const ctx = document.getElementById('price-chart').getContext('2d');
        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: Array(100).fill(''),
                datasets: [{
                    label: 'Price',
                    data: this.state.priceHistory[this.selectedCoin],
                    borderColor: '#b5bd68',
                    borderWidth: 1,
                    fill: false,
                    tension: 0.4
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                animation: false,
                scales: {
                    x: {
                        display: false
                    },
                    y: {
                        display: true,
                        color: '#c5c8c6',
                        grid: {
                            color: '#373b41'
                        }
                    }
                },
                plugins: {
                    legend: {
                        display: false
                    }
                }
            }
        });
    }

    updatePrices() {
        const coins = ['NEET', 'TENDIE', 'WAGIES', 'PEPE'];
        coins.forEach(coin => {
            // Random walk with increased volatility
            const volatility = 0.15; // 15% price movement
            const change = (Math.random() - 0.5) * 2 * volatility;
            
            // Add chance for extreme moves
            const extremeEvent = Math.random() < 0.02; // 2% chance
            const extremeMultiplier = Math.random() < 0.5 ? 0.5 : 2; // 50% up or down

            let newPrice = this.state.prices[coin] * (1 + change);
            if (extremeEvent) {
                newPrice *= extremeMultiplier;
                this.addNotification(`>${coin} just had a ${extremeMultiplier > 1 ? 'pump' : 'dump'}!`, 'important');
            }

            // Keep price within reasonable bounds
            newPrice = Math.max(1, Math.min(100000, newPrice));
            
            this.state.prices[coin] = newPrice;
            this.state.priceHistory[coin].push(newPrice);
            this.state.priceHistory[coin].shift();
        });

        // Update chart for selected coin
        this.updateChart();
    }

    updateChart() {
        const prices = this.state.priceHistory[this.selectedCoin];
        this.chart.data.datasets[0].data = prices;
        this.chart.data.datasets[0].label = `${this.selectedCoin}/USD`;
        this.chart.update('none');

        // Update current price display
        document.getElementById('current-price').querySelector('span').textContent = 
            `$${this.state.prices[this.selectedCoin].toFixed(2)}`;
    }

    executeTrade(isBuy) {
        const amount = parseFloat(document.getElementById('trade-amount').value);
        if (isNaN(amount) || amount <= 0) {
            this.addNotification('>invalid trade amount', 'error');
            return;
        }

        const price = this.state.prices[this.selectedCoin];
        const total = amount * price;

        if (isBuy) {
            if (total > this.state.portfolio) {
                this.addNotification('>not enough funds', 'error');
                return;
            }
            this.state.holdings[this.selectedCoin] = (this.state.holdings[this.selectedCoin] || 0) + amount;
            this.state.portfolio -= total;
            this.addNotification(`>bought ${amount} ${this.selectedCoin} @ $${price.toFixed(2)}`, 'success');
            this.updateWaifuDialogue('bigWin');
        } else {
            if (amount > (this.state.holdings[this.selectedCoin] || 0)) {
                this.addNotification('>not enough coins', 'error');
                return;
            }
            this.state.holdings[this.selectedCoin] -= amount;
            this.state.portfolio += total;
            this.addNotification(`>sold ${amount} ${this.selectedCoin} @ $${price.toFixed(2)}`, 'success');
            this.updateWaifuDialogue('bigLoss');
        }

        this.updateStats();
    }

    updateStats() {
        // Update portfolio value including holdings
        let totalValue = this.state.portfolio;
        Object.keys(this.state.holdings).forEach(coin => {
            totalValue += this.state.holdings[coin] * this.state.prices[coin];
        });

        // Update displays
        document.getElementById('portfolio-value').querySelector('.stat-value').textContent = 
            `$${totalValue.toFixed(2)}`;
        document.getElementById('gbp-display').querySelector('.stat-value').textContent = 
            `${this.state.gbp} GBP`;
        
        // Update holdings display
        const holdingsDiv = document.getElementById('holdings-display').querySelector('.holdings-list');
        const holdings = Object.entries(this.state.holdings)
            .filter(([_, amount]) => amount > 0)
            .map(([coin, amount]) => {
                const value = amount * this.state.prices[coin];
                return `>${coin}: ${amount.toFixed(2)} ($${value.toFixed(2)})`;
            });
        
        holdingsDiv.innerHTML = holdings.length > 0 ? 
            holdings.join('<br>') : 
            '>no bags yet anon';

        // Check win condition
        if (totalValue >= 200000) {
            document.getElementById('apartment-btn').classList.remove('hidden');
        }
    }

    startGame() {
        this.isPlaying = true;
        document.getElementById('start-screen').classList.add('hidden');
        document.getElementById('game-area').classList.remove('hidden');
        this.gameLoop();
        this.startWaifuSpawner();
        this.updateWaifuDialogue('greeting');
    }

    gameLoop() {
        if (!this.isPlaying) return;

        const now = Date.now();
        const deltaTime = (now - this.lastUpdate) / 1000;
        this.lastUpdate = now;

        // Update game state
        this.state.stress = Math.min(100, this.state.stress + deltaTime * 2);
        this.state.hunger = Math.min(100, this.state.hunger + deltaTime * 1.5);

        // Check conditions
        if (this.state.stress > 80) {
            this.updateWaifuDialogue('needShower', true);
        }
        if (this.state.hunger > 80) {
            this.updateWaifuDialogue('needFood', true);
        }

        // Update prices every second
        if (now - this.lastPriceUpdate > 1000) {
            this.updatePrices();
            this.lastPriceUpdate = now;
        }

        this.updateStats();
        requestAnimationFrame(() => this.gameLoop());
    }

    setupEventListeners() {
        // Trading controls
        document.getElementById('buy-btn').addEventListener('click', () => this.executeTrade(true));
        document.getElementById('sell-btn').addEventListener('click', () => this.executeTrade(false));
        document.getElementById('coin-selector').addEventListener('change', (e) => {
            this.selectedCoin = e.target.value;
            this.updateChart();
        });

        // Action buttons
        document.getElementById('shower-btn').addEventListener('click', () => this.takeShower());
        document.getElementById('tendies-btn').addEventListener('click', () => this.eatTendies());
        document.getElementById('apartment-btn').addEventListener('click', () => this.buyApartment());
        
        // Start button
        document.getElementById('start-btn').addEventListener('click', () => this.startGame());
    }

    // ... (keep the rest of the waifu-related methods)
}

// Initialize game when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    window.game = new Game();
});
