# Simple Console Game – (C++)

A simple console-based project written in C++.  
The game focuses on an inventory system, item management, equipment, and an in-game store.
Player can buy, sell, upgrade, and repair items while earning money through gameplay.

---

## Features

### Inventory System
- Grid / slot based inventory.
- Store multiple items at once.
- Item selection using row and column.
- Item rarity system (Common, Uncommon, Rare, Epic, Legendary, Unknown).
- Item type system  (Wooden -> Stone -> Iron -> Gold -> Diamond -> Unseen).
- Item durability / condition that decreases while playing, and that can be restored.
- Show info for items.

### Equipped Items
- Separate equipment slots (melee, ranged and armor).
- Equipped items directly affect gameplay rewards.
- Ability to equip and unequip items from inventory.

### Shop
- Buy new items using in-game currency.
- Random item rarity generation.

### Sell System
- Sell unwanted items from inventory.
- Selling price depends on rarity, type and condition.

### Play Mode
- Main gameplay loop where the player earns money.
- Rewards depend on:
  - Armor strength (better armor - less money lost)
  - Weapon rarity
  - Item condition
- Items lose durability after each play session.
- Chance of zombie attacking resulting in losing money.

### Upgrading Items
- Increase type by one.
- Costs in-game currency.

### Repair System
- Restore item durability after it has been worn down.
- Repair cost depends on type and damage level.

### Secret Codes / Extras
- Hidden commands/cheat codes.
- One-time used.

### Navigation guide and map
- Non-functional map.
- Full navigation guide.

## Project Structure
  - main.cpp
  - item.h item.cpp
  - inventory.h inventory.cpp
  - player.h player.cpp
  - game.h game.cpp
  - charCheck.h
  - random.h random.cpp
  - menu.h menu.cpp
  - shop.h shop.cpp
  - store.h store.cpp
  - gridbase.h gridbase.cpp
  - equipment.h equipment.cpp


---

## How to Run (macos)
1. Go to project location in terminal using cd:
```
.../project_folder
```
2. Compile:
```
g++ -std=c++17 -Wall *.cpp -o inventory
```
3. Run:
```
./inventory
```

---

# Build Instructions (Windows)
Have fun :))

## ✔️ Variant 1 — MSYS2 Already Installed

This project requires **MSYS2** with `g++`.

If you already have **MSYS2** installed:

1. Open **MSYS2 UCRT64** terminal.
2. Navigate to the project directory:
```
cd /c/path/to/project
```
### 3. Compile the program:
```
g++ *.cpp -o game.exe
```
### 4. Run the program:
```
./program.exe
```
## ❌ Variant 2 — MSYS2 Not Installed
### 1. Install MSYS2

Download MSYS2 from the [official website](https://www.msys2.org/).

Install it using the default path (recommended: C:\msys64).

### 2. Update Packages

Open MSYS2 UCRT64 and run:
```
pacman -Syu
```

If prompted to restart the terminal:

- Close it

- Open MSYS2 UCRT64 again

- Run the same command:
```
pacman -Syu
```
### 3. Install g++

In the MSYS2 terminal, run:
```
pacman -S mingw-w64-ucrt-x86_64-gcc
```
Confirm installation with Y.

### 4. Build the Project

Navigate to your project folder:

cd /c/path/to/project 	(to make it work always use **"/" not "\"**  and disk name must be **"/disk letter/"**) ⚠️

Compile:
```
g++ *.cpp -o game.exe
```
Before run:
```
clear
```
Run:
```
./game.exe
```
### Verifying installation:

Run:
```
g++ --version
```
## All of commands must be run in MSYS2 Terminal ‼️
---

## Purpose

This project is designed for learning:
- Object-oriented design in C++
- Class relationships and data management
- Game logic and state handling
- Console UI interaction
