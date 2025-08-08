355 Snake Game
Classic Snake game implemented in C for the CS 355 Systems Programming course, Fall 2020.

🔍 Project Overview
A terminal-based Snake game built using the ncurses library. Players control a snake that moves inside a bordered play area, eating numbered trophies to grow longer. The game speeds up as the snake grows and ends when the snake hits the border, itself, or attempts to reverse direction.

🎮 Key Features
🕹️ Snake Movement & Growth
Initial length: 3 characters, random starting direction.

Controlled with arrow keys, no reversing allowed.

Speed increases proportionally with length.

🎯 Trophies
One trophy displayed at a time, digit 1–9.

Eating a trophy grows the snake by that number.

Trophies expire after 1–9 seconds and respawn randomly.

⚠️ Gameplay Rules
Game over if snake hits border or itself.

User cannot reverse the snake’s direction.

Win by growing snake to half the border’s perimeter length.

📅 Milestones
Intermediate deliverable (due 11/25/2020):

Snake size 5 moving right, movement control, visible border, no trophies or growth.

Final deliverable (due 12/07/2020):

Full gameplay with trophies, growth, and all rules.

🛠️ Tools Used
C programming language

ncurses library for terminal UI

Linux terminal environment (e.g., Google Cloud Console)

📹 Submission
Single C source file implementing the game.

Short gameplay video screencast (max 3 minutes).
