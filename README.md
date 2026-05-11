<div align="center">

# Console RPG Inventory System
### *A C++ console game built around deep item management*

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Windows-lightgrey?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=for-the-badge)
<br/>

> Buy. Sell. Upgrade. Survive. Don't let the zombies take your gold.

</div>

---

## Overview

A console-based RPG written in **C++17**, centered around a rich inventory and item management system. Equip weapons, manage durability, run the shop, earn money — and now enjoy **background music** — all from your terminal.

The project is structured across multiple modules: `item`, `inventory`, `equipment`, `shop`, `player`, `game`, `music`, and display utilities — making it a solid example of object-oriented design in a game context.

---

## Project Structure

```
inventory/
├── src/
│   ├── main.cpp          # Entry point
│   ├── game.cpp/h        # Core game loop & logic
│   ├── inventory.cpp/h   # Inventory grid management
│   ├── item.cpp/h        # Item class (rarity, type, durability)
│   ├── equipment.cpp/h   # Equipment slots (melee, ranged, armor)
│   ├── shop.cpp/h        # Buy/sell system
│   ├── player.cpp/h      # Player stats & state
│   ├── music.cpp/h       # Background music (via miniaudio)
│   ├── gridbase.cpp/h    # Grid rendering base
│   ├── displaylist.cpp/h # Console display utilities
│   ├── random.cpp/h      # RNG utilities
│   ├── charCheck.h       # Input validation
│   └── miniaudio.h       # Single-header audio library
├── include/
├── music/                # Audio files
├── CMakeLists.txt
└── documentation.docx
```

---

## Features

<details>
<summary><b>🎒 Inventory System</b></summary>
<br/>

- Grid/slot-based inventory with row & column item selection
- Store and manage multiple items simultaneously
- **Rarity tiers:** `Common` → `Uncommon` → `Rare` → `Epic` → `Legendary` → `Unknown`
- **Item types:** `Wooden` → `Stone` → `Iron` → `Gold` → `Diamond` → `Unseen`
- Item durability that degrades over time and can be restored
- Detailed item info display
- Expand inventory slots using backpacks

</details>

<details>
<summary><b>⚔️ Equipment Slots</b></summary>
<br/>

- Dedicated slots for **Melee**, **Ranged**, and **Armor**
- Equipped items directly impact gameplay rewards
- Freely equip and unequip items from inventory

</details>

<details>
<summary><b>🏪 Shop & Economy</b></summary>
<br/>

- Buy new items using in-game currency
- Random rarity generation on shop items
- Sell unwanted items — price depends on **rarity**, **type**, and **condition**

</details>

<details>
<summary><b>⚔️ Play Mode</b></summary>
<br/>

- Core gameplay loop for earning money
- Rewards scale with:
  - Armor strength — better armor means less money lost
  - Weapon rarity
  - Item condition
- Items degrade after each session
- Random zombie attack events — watch your wallet
- Small chance of a boss fight: big risk, big reward
- Heal yourself with medkits when HP is low

</details>

<details>
<summary><b>🔧 Upgrade & Repair</b></summary>
<br/>

- **Upgrade:** Increase an item's type tier by one (costs currency)
- **Repair:** Restore item durability — cost scales with type and damage level

</details>

<details>
<summary><b>💾 Save & Load</b></summary>
<br/>

The game features a **per-user save system** — progress is tied to a username, so multiple players can each have their own save file on the same machine.

- Progress is saved to a file named after your username
- Saves include: inventory contents, equipped items, player stats, currency, and session statistics
- Access the save menu from the main game screen (`STATE_SAVE`)
- On startup, the game prompts you to **load an existing save** or **start fresh**
- You can also **delete a save** for a given user from the load screen

> ⚠️ There is currently **no auto-save** — remember to save manually before quitting or your progress will be lost.

</details>

<details>
<summary><b>🎵 Background Music</b></summary>
<br/>

- In-game background music powered by [miniaudio](https://miniaud.io/) — a single-header C/C++ audio library
- Music files are stored in the `music/` directory
- Audio plays automatically and runs on a separate thread

</details>

<details>
<summary><b>🗺️ Navigation & Map</b></summary>
<br/>

- Full in-game navigation guide
- Decorative map (cosmetic only)

</details>

<details>
<summary><b>🔑 Secret Codes</b></summary>
<br/>

- Hidden cheat commands for the curious
- One-time use only — choose wisely

</details>

---

## How to Build & Run

### macOS

```bash
# 1. Clone and enter the repo
git clone https://github.com/megajohn150/inventory.git && cd inventory

# 2. Create a build directory
mkdir build && cd build

# 3. Configure with CMake
cmake ..

# 4. Build
make

# 5. Run
./inventory
```

---

### Windows

<details>
<summary><b>Variant 1 — MSYS2 Already Installed ✔️</b></summary>
<br/>

1. Open **MSYS2 UCRT64** terminal
2. Navigate to the project:

```bash
cd /c/path/to/project
```

3. Compile:

```bash
g++ src/*.cpp -o game.exe -I src
```

4. Clear terminal and run:

```bash
clear
./game.exe
```

</details>

<details>
<summary><b>Variant 2 — MSYS2 Not Installed ✖️</b></summary>
<br/>

**Step 1 — Install MSYS2**

Download from [msys2.org](https://www.msys2.org/) and install to the default path (`C:\msys64` recommended).

**Step 2 — Update packages**

Open **MSYS2 UCRT64** and run:

```bash
pacman -Syu
```

> If prompted to restart — close, reopen, and run again.

**Step 3 — Install g++**

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Confirm with `Y`.

**Step 4 — Build & Run**

Navigate to your project folder:

```bash
cd /c/path/to/project
```

> Always use `/` (forward slash), not `\`. Disk letter format: `/c/`, `/d/`, etc.

```bash
g++ src/*.cpp -o game.exe -I src
clear
./game.exe
```

**Verify your install:**

```bash
g++ --version
```

> All commands must be run inside the **MSYS2 terminal**.

</details>

---

## Dependencies

| Library | Purpose | Bundled |
|---------|---------|---------|
| [miniaudio](https://miniaud.io/) | Cross-platform audio playback | ✅ Yes (`src/miniaudio.h`) |
| CMake ≥ 3.10 | Build system | ❌ Install separately |
| g++ / clang++ (C++17) | Compiler | ❌ Install separately |

---

## Purpose

This project was built to practice and explore:

- Object-oriented design in C++ across multiple interacting classes
- Class relationships, inheritance, and data encapsulation
- Game loop design and state management
- Console UI rendering and user input handling
- Integrating a third-party single-header library (miniaudio)

---

<div align="center">
  <sub>Built with ☕ and too much time in a terminal by megajohn150 & SlvxShybitskyi</sub>
</div>
