# South Dakota Smith and the Temple of Doom

## Overview

**South Dakota Smith and the Temple of Doom** is an action-adventure game built in C++ in which the player navigates through a multi-level temple represented by an 18x70 grid with ASCII characters, using weapons and scrolls to fight monsters and find the golden idol 

## Game Description

In this game, you play as an adventurer navigating a 5-level temple in search of the golden idol. Each level is a randomly generated maze, filled with various monsters and objects. The game is turn-based, allowing the player to carefully plan each move as they encounter different challenges.

### Features

- **Temple Exploration:**  
  The game features a 5-level temple, each level randomly generated and filled with interconnected rooms and corridors.

- **Monsters:**  
  Encounter a variety of monsters, including:
  - **Bogeymen ('B')**
  - **Dragons ('D')**
  - **Goblins ('G')**
  - **Snakewomen ('S')**
  Each monster has unique behaviors and attack patterns.

- **Objects:**  
  Collect and use various objects to aid in your journey:
  - **Weapons ( ')' )**: Maces, Short Swords, Long Swords, Magic Fangs of Sleep, Magic Axes
  - **Scrolls ('?')**: Scrolls of Teleportation, Improve Armor, Raise Strength, Enhance Health, Enhance Dexterity
  - **The Golden Idol ('&')**: The key to winning the game.

- **Combat System:**  
  Engage in battles using different weapons. Each weapon has specific stats that influence combat outcomes, such as dexterity bonuses and damage points.

- **Inventory Management:**  
  Manage an inventory of up to 25 items, including weapons and scrolls. Equip different weapons and read scrolls to gain advantages in the game.

- **Game Interface:**  
  The game uses simple keyboard commands for movement, combat, and item management, making it easy to navigate and play.

### Technical Implementation

- **Object-Oriented Design:**  
  The game is built using object-oriented principles, including inheritance and polymorphism. Different game elements like monsters, weapons, and scrolls are implemented as classes, allowing for modular and reusable code.

- **Recursive Algorithms:**  
  Certain monsters, like Goblins, utilize recursive algorithms to search for the player, making the game more challenging and dynamic.

- **Game Objects:**  
  Game objects such as weapons and scrolls are managed using vectors of class pointers, allowing for easy manipulation and interaction within the game environment.

### Controls

- **Movement:**  
  Use the arrow keys or `h`, `j`, `k`, `l` to move left, down, up, and right, respectively.

- **Combat:**  
  Attack monsters by moving into their direction.

- **Pick Up Items:**  
  Stand on an item and press `g` to pick it up.

- **Wield Weapon:**  
  Press `w` to select and wield a weapon from your inventory.

- **Read Scroll:**  
  Press `r` to select and read a scroll from your inventory.

- **Inventory:**  
  Press `i` to view your inventory.

- **Descend Stairs:**  
  Stand on a stairway and press `>` to descend to the next level.

- **Quit Game:**  
  Press `q` to quit the game.

## License

This game was developed for educational purposes and is provided as-is without any warranty.
