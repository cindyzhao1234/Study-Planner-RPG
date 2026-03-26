# Study Planner RPG

A C++ game-inspired productivity app where players complete tasks to earn coins, buy cosmetic items, and customise their character through an inventory and shop system.

## Overview

Study Planner RPG combines a practical to-do list with a light RPG-style reward loop. Players complete tasks to earn coins, then spend those coins on cosmetic items such as hats, hairstyles, tops, and bottoms. Owned items can be equipped through an inventory popup, and the character is rendered with layered accessories on both the home screen and preview panels.

I built this project to strengthen my C++ skills, turning a simple To-Do list concept into a system that feels interactive and game based.

## Resume Pitch

This project showcases:
- C++ class-based program design
- UI/gameplay programming with Raylib
- shared state management across multiple systems
- file-based item loading with CSV
- modular rendering and update logic
- player-facing reward and customisation systems

## Features

- **Task system**
  - add tasks
  - wrapped task text
  - task scrolling
  - task completion checkboxes
  - delete task button
- **Reward loop**
  - completing tasks grants coins
- **Inventory system**
  - category filters for all / hat / hair / top / bottom
  - owned item display
  - equip / unequip logic
- **Shop system**
  - category filters
  - selected item preview
  - owned / available states
  - purchase flow using coins
  - temporary success / insufficient coins messages
- **Character customisation**
  - layered rendering of base character plus equipped accessories
- **Data-driven items**
  - item metadata loaded from CSV instead of fully hardcoded game logic

## Tech Stack

- **Language:** C++
- **Graphics / Windowing:** Raylib
- **Data loading:** CSV file parsing
- **Core containers:** `std::vector`, `std::unordered_map`, `std::string`

## Project Structure

- `main.cpp`  
  Coordinates the main game loop, update order, and drawing order.

- `TaskManager`  
  Handles the to-do list panel, text wrapping, scrolling, input handling, task completion, and delete logic.

- `Inventory`  
  Displays owned items, supports category filtering, and handles equip / unequip interactions.

- `Shop`  
  Displays shop items, handles filtering, previews selected items, and processes purchases.

- `CharacterRenderer`  
  Draws the player character using layered textures so equipped accessories render in the correct order.

- `Assets`  
  Loads and unloads textures used throughout the project.

- `ItemLoader`  
  Reads item definitions from CSV into item structs used by the inventory, shop, and renderer.

## Technical Highlights

- Built multiple UI systems from scratch in C++
- Separated **update logic** from **rendering logic**
- Implemented wrapped text and dynamic task height calculation
- Added scrolling and clipping for the task list using scissor mode
- Used shared item state for ownership and equipment tracking
- Implemented layered rendering for character customisation
- Moved item definitions into CSV for a more data-driven workflow
- Refactored from hardcoded single-item logic toward reusable systems

## C++ Concepts Demonstrated

- class design and encapsulation
- references and const-correctness
- STL containers and iteration
- file I/O and CSV parsing
- lookup structures for loaded textures
- frame-based UI and state updates
- debugging of interaction and rendering issues
- modular `.h` / `.cpp` project organisation

## Testing and Debugging

This project was developed iteratively with a strong focus on debugging interactive systems. During development, I worked through issues such as:

- mismatched draw/update hitboxes
- popup UI overlapping with background task controls
- incorrect shared state between task rewards and shop purchases
- item ownership/equipment consistency
- text wrapping and task height calculation
- timer-based popup feedback messages
- file path and asset loading errors
- sprite layering order for hats, hair, tops, and bottoms

While the project does not yet include formal automated tests, it is structured modularly so that systems like purchasing, equipping, and text wrapping could be tested more cleanly in future iterations.

## Player Experience Focus

A major goal of the project was to make productivity feel more rewarding and engaging. I wanted the user experience to include:

- immediate feedback for completed tasks
- a simple progression loop through coins
- clear visual states for owned, equipped, and purchasable items
- character customisation as a form of player expression
- readable, game-like UI panels rather than a plain checklist

## Current Limitations

- UI art and scaling are still being refined
- item texture loading is still partially being generalised
- no save/load system yet
- no formal automated test suite yet

## Future Improvements

- save/load support for:
  - tasks
  - coins
  - owned items
  - equipped items
- better item-to-texture mapping through asset keys in CSV
- improved shop preview rendering
- more polish for popup panels and UI scaling
- sound effects and animation feedback
- automated testing for:
  - purchase logic
  - inventory filtering
  - equipment state
  - text wrapping
- more progression systems, such as unlocks or streak rewards

## How to Run

1. Install Raylib and your required C++ build dependencies.
2. Build the project using your local build setup.
3. Run the executable.
4. Complete tasks to earn coins.
5. Open the shop to purchase cosmetics.
6. Open the inventory to equip owned items.

<!-- ## Screenshots / Demo

_Add screenshots or a short GIF here._

Suggested visuals:
- home screen with task panel and character
- inventory popup
- shop popup
- character wearing purchased accessories -->

## Why I Built This

I wanted to practise C++ through a project that felt closer to an actual game system than a standard coursework exercise. This project let me work on rendering, interaction, UI logic, state management, and data-driven design while also showing genuine interest in games and player-facing experiences.