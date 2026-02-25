<div align="center">

# Console RPG Inventory System
### *A C++ console game built around deep item management*

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Windows-lightgrey?style=for-the-badge)
<br/>

> Buy. Sell. Upgrade. Survive. Don't let the zombies take your gold.

</div>

---

## Overview

A console-based RPG project written in **C++**, focused on a rich inventory and item management system. Equip weapons, manage durability, run the shop, and earn money — all from your terminal.

---

## Features

<details>
<summary><b>Inventory System</b></summary>
<br/>

- Grid/slot-based inventory with row & column item selection
- Store and manage multiple items simultaneously
- **Rarity tiers:** `Common` → `Uncommon` → `Rare` → `Epic` → `Legendary` → `Unknown`
- **Item types:** `Wooden` → `Stone` → `Iron` → `Gold` → `Diamond` → `Unseen`
- Item durability that degrades over time and can be restored
- Detailed item info display

</details>

<details>
<summary><b>Equipment Slots</b></summary>
<br/>

- Dedicated slots for **Melee**, **Ranged**, and **Armor**
- Equipped items directly impact gameplay rewards
- Equip and unequip items freely from inventory

</details>

<details>
<summary><b>Shop & Economy</b></summary>
<br/>

- Buy new items using in-game currency
- Random rarity generation on shop items
- Sell unwanted items — price depends on **rarity**, **type**, and **condition**

</details>

<details>
<summary><b>Play Mode</b></summary>
<br/>

- Core gameplay loop for earning money
- Rewards scale with:
  - Armor strength — better armor means less money lost
  - Weapon rarity
  - Item condition
- Items degrade after each session
- Random zombie attack events — watch your wallet
- Small chance of boss fight occuring: big risk - big reward
- If you are low on hp, heal yourself using medkits!

</details>

<details>
<summary><b>Upgrade & Repair</b></summary>
<br/>

- **Upgrade:** Increase an item's type tier by one (costs currency)
- **Repair:** Restore item durability — cost scales with type and damage level

</details>

<details>
<summary><b>Secret Codes</b></summary>
<br/>

- Hidden cheat commands for the curious
- One-time use only — choose wisely

</details>

<details>
<summary><b>Navigation & Map</b></summary>
<br/>

- Full navigation guide included
- Decorative in-game map (non-functional, purely cosmetic)

</details>

---

## How to Run

### macOS

**1. Clone repository in desired location and enter it:**
```
git clone https://github.com/megajohn150/inventory.git && cd inventory
```
**2. Create a build directory and enter it:**
```
mkdir build && cd build
```
**3. Configure with CMake:**
```
cmake ..
```
**3. Build the project:**
```
make
```
**4. Run:**
```
./inventory
```
---

### Windows

Two paths depending on your setup:

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
g++ *.cpp -o game.exe
```

4. Clear terminal, then run:

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
g++ *.cpp -o game.exe
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

## Purpose

This project was built to practice and explore:

- Object-oriented design in C++
- Class relationships and data management
- Game logic and state handling
- Console UI interaction

---

<div align="center">
  <sub>Built with ☕ and too much time in a terminal.</sub>
</div>
