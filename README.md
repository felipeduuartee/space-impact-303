# Space Impact 303

## Project Overview
This project is a reimagined version of the classic "Space Impact 303" game, developed in C using the Allegro 5 library. It features dynamic shoot 'em up gameplay with unique levels, enemies, and mechanics inspired by the original Nokia game. The project adheres to the requirements of a Programming II course assignment, with both mandatory features and optional enhancements.

## Features

### Core Features (80% of Grade)

1. **Levels**
   - **Two unique levels**, each with its own background and design.
   - Levels last at least 30 seconds each.

2. **Player Ship**
   - Animated sprite for the player ship, including movement animations.
   - A health system (HP) that ends the game when it reaches zero.
   - Standard attack available throughout the game.

3. **Enemies**
   - Each level features **two types of normal enemies**, with unique sprites (four enemy types in total).
   - Two enemy types launch projectiles.
   - One stationary enemy type, while others have movement patterns.

4. **Boss Fights**
   - Each level culminates in a **unique boss fight**.
   - Bosses have at least two distinct attacks, including one projectile-based attack.
   - Bosses have significantly higher health and provide a challenge to the player.

5. **Special Attacks**
   - The player can acquire **two temporary special attacks** (duration: max 5 seconds).
   - Special attacks must be collected on the map.

### Optional Features (20% of Grade)

1. **Story Integration**
   - Introductory screen in "Star Wars" style explaining the game's backstory.
   - Player and boss dialogues before and after levels.
   - A final screen summarizing the mission's outcome and its implications.

## Installation and Usage

### Prerequisites
- **Allegro 5 Library**: Install Allegro 5 on your system by following the [official documentation](https://liballeg.org/a5docs/trunk/).
- A standard C compiler (e.g., GCC).

### Compilation
Use the provided Makefile to compile the game:

```bash
make
```

To clean compiled files:

```bash
make clean
```

### Running the Game
To run the game:

```bash
./jogo
```

## Game Controls
- **WASD**: Move the player ship.
- **Space Bar**: Fire standard attack.
- **Special Attack Keys**: (E).

## Development Process

### Phase 1: Planning
- Delivered a PDF document outlining the project structure, module dependencies, and development timeline.
- The document specified the segmentation of work and order of implementation.

### Phase 2: Development
- Development took place from **24/10/2024 to 08/12/2024**.
- Core gameplay features were implemented, followed by optional enhancements.

### Phase 3: Testing and Defense
- Tested for bugs, including handling of segmentation faults.
- Project defense includes demonstrating functionality and implementing a live modification.

## Optional Enhancements
- Additional game modes or mechanics can be added for extra credit.
- Use external sprite assets from [Itch.io](https://itch.io/game-assets/free/tag-spaceship) or create your own.

## Known Issues
- Ensure Allegro 5 is correctly installed; otherwise, runtime errors may occur.

