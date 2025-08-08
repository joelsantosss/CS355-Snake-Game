# 355-snake-game

This C terminal-based Snake game was built to implement the classic snake gameplay with trophies and increasing difficulty as part of the CS 355 Systems Programming course.

## 🔍 Project Overview

The game uses the ncurses library to create a bordered snake pit in the terminal where players control a snake that grows by eating numbered trophies. The snake speeds up as it grows, and the game ends if the snake collides with the border, itself, or if the player tries to reverse direction. The objective is to grow the snake to half the perimeter of the playing area.

## 🎮 Key Features

### 🕹️ Snake Movement & Growth
- **Initial length**: 3 characters, random starting direction  
- **Control**: Arrow keys, no reversing allowed  
- **Speed**: Increases with snake length  

---

### 🎯 Trophies
- **One trophy** displayed at a time (digits 1–9)  
- **Growth**: Eating a trophy increases snake length by its digit  
- **Expiry**: Trophy expires after 1–9 seconds and respawns randomly  

---

### ⚠️ Gameplay Rules
- **Game over**: If snake hits border or itself  
- **No reversing**: Player cannot reverse snake direction  
- **Win condition**: Snake length reaches half the border’s perimeter  

---

## 📅 Milestones

### 🐢 Intermediate Deliverable (due 11/25/2020)
- Snake size 5 moving right  
- Full directional control  
- Visible snake pit border  
- No growth or trophies  

---

### 🐍 Final Deliverable (due 12/07/2020)
- Full gameplay with trophies, growth, and enforced rules  

---

## 🛠️ Tools Used

- **C programming language**  
- **ncurses** terminal UI library  
- Linux terminal environment (e.g., Google Cloud Console)  

---

## 📁 File

- [snake.c](./snake.c)

---

## 📫 Contact

Feel free to connect or ask questions:  
- [LinkedIn](https://www.linkedin.com/in/joelsantossss)  
- [Email](mailto:joelsantos@my.ccsu.edu)
