 RPG Battle Game (C++)

## About the Project
The RPG Battle Game is a turn-based combat game developed in C++ as a Data Structures and Algorithms (DSA) project. The player chooses a character class and battles against different enemies across multiple waves, including a final boss.

The project demonstrates the practical implementation of fundamental data structures through game mechanics such as inventory management, turn handling, and action history.

## Features
- Three playable character classes: Warrior, Mage, and Archer.
- Turn-based combat system.
- Multiple enemy battles with increasing difficulty.
- Inventory system for managing and using items.
- Special abilities for different character classes.
- Undo functionality to reverse the most recent recorded action.

## Data Structures Implemented

### 1. Singly Linked List
Used for inventory management. It stores inventory items dynamically and allows the player to add, display, and use items.

### 2. Stack
Used to maintain the history of player actions and implement the undo functionality. It follows the **Last In, First Out (LIFO)** principle.

### 3. Queue
Used to manage the turn order of the hero and enemies. It follows the **First In, First Out (FIFO)** principle.

## Technologies Used
- C++
- Object-Oriented Programming (OOP)
- Data Structures and Algorithms (DSA)

## How to Run
1. Clone or download this repository.
2. Open the project in a C++ IDE, such as Dev-C++ or Visual Studio Code.
3. Compile the source code using a C++ compiler.
4. Run the compiled program and start playing.

Alternatively, if using g++, run:

```bash
g++ main.cpp -o RPGGame
./RPGGame
```

Replace `main.cpp` with the actual name of your source file if it is different.

## Learning Outcomes
This project helped us understand how data structures can be applied to real-world programming scenarios. It demonstrates how linked lists, stacks, and queues can work together to manage game inventory, action history, and turn-based combat.

## Project Type
Academic Project – Data Structures and Algorithms (DSA)
