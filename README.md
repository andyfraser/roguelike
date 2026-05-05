# Terminal Roguelike

A classic, terminal-based Roguelike game built in C using the `ncurses` library. Explore procedurally generated dungeons, battle diverse monsters, and level up your character in this retro-inspired RPG experience.

## Features

- **Procedural Dungeon Generation:** Every playthrough features a unique map with varied rooms and corridors.
- **Class-Based Gameplay:** Choose your path as a **Warrior**, **Mage**, or **Rogue**, each with distinct starting stats and abilities.
- **Scaling Difficulty:** Face 30+ monsters per level that grow stronger (20% stat boost per level) as you do.
- **Ranged Magic:** Harness the power of the Mage's **Fireball** to incinerate visible enemies from a distance.
- **Persistent Message Log:** Keep track of your battles, item pickups, and level-ups with a built-in logging system.
- **Field of View (FOV):** Explore the darkness; only tiles within your line of sight are revealed.
- **Robust Testing:** Includes a dedicated unit testing suite to ensure game balance and stability.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc` or `clang`).
- `ncurses` development libraries.
  - On macOS: `brew install ncurses`
  - On Ubuntu/Debian: `sudo apt-get install libncurses5-dev libncursesw5-dev`

### Installation & Build

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/rougelike.git
   cd rougelike
   ```
2. Build the game using the provided Makefile:
   ```bash
   make
   ```
3. Run the game:
   ```bash
   ./roguelike
   ```

### Running Tests

To verify the game's core logic, run the unit testing suite:
```bash
make test
```

## Documentation

Detailed gameplay information can be found in the [User Manual](./docs/USER_MANUAL.md).

For development conventions and architectural details, see [GEMINI.md](./GEMINI.md).

## License

This project is open-source and available under the MIT License.
