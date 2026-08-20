# 🎩 Monopoly_LK

A fully functional, terminal-based implementation of the classic Monopoly board game, written entirely in C. 

This project was developed to apply foundational computer science concepts—such as data structures, memory management, and control flow—to a complex logic problem. To ensure clean and maintainable code, the architecture is heavily modularized, separating core game mechanics into distinct files for player state management, virtual finances, and board events.

## 🚀 Features

*   **Terminal-Based Gameplay:** Play a full game of Monopoly directly from your command line.
*   **Modular Architecture:** The codebase is split into specific, single-responsibility files for cleaner logic and easier debugging.
*   **Virtual Economy:** Robust handling of player balances, property purchases, and rent calculations.
*   **Dynamic Events:** Manages complex board interactions and turn-based player states.

## 📁 Project Structure

The game logic is divided into the following core modules:

*   `main.c` & `game.c`: Controls the primary game loop, initialization, and overarching rules.
*   `board.c`: Manages the layout of the board, property details, and spaces[cite: 1].
*   `players.c`: Handles individual player data, turns, movement, and ownership states[cite: 1].
*   `finance.c`: The economic engine responsible for tracking money, transactions, and rent[cite: 1].
*   `events.c`: Triggers and resolves specific board events (e.g., landing on special tiles)[cite: 1].
*   `types.h`: A shared header file defining the core data structures (`structs`) used across the game[cite: 1].

## 🛠️ Prerequisites & Compilation

To run this game, you will need a C compiler (like `gcc`) installed on your system.

### How to Build and Run (Linux / macOS)

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/RansikaMandiv/Monopoly_LK.git](https://github.com/RansikaMandiv/Monopoly_LK.git)
   cd Monopoly_LK

2. **Compile the Source files:**
   ```bash
   gcc *.c -o monopoly

3.**Execute the Game:**
   ```bash
  ./monopoly
```

## 🧠 Learning Outcomes

Building Monopoly_LK served as a deep dive into practical software development. Key takeaways include:

*   Mastering modular C programming by linking multiple `.c` and `.h` files.
*   Implementing and managing complex data structures to track game states.
*   Utilizing Git for version control and maintaining a clean development workflow through the Linux terminal.
