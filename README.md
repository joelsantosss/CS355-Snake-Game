355 Snake Game
Classic Snake game implemented in C for the CS 355 Systems Programming course (Fall 2020).

🐍 Project Overview
This project implements the classic Snake game in the terminal using the curses/ncurses library. The snake moves around a bordered play area (“snake pit”) within the terminal window, growing by eating numbered trophies that appear randomly.

🎮 Key Features
🕹️ Snake Movement & Growth
Initial snake length of 3, moving in a random direction.

Controlled by arrow keys (no reversing allowed).

Speed increases proportionally with snake length.

🎯 Trophies
One trophy displayed at a time, represented by a digit (1-9).

Eating a trophy increases snake length by that digit’s value.

Trophies expire after 1-9 seconds and respawn elsewhere.

⚠️ Gameplay Rules
Game ends if the snake hits the border or itself, or tries to reverse direction.

Player wins when snake length reaches half the perimeter of the pit.

📚 Course Requirements
Use curses/ncurses for all visuals.

Code must be well-commented with author and function descriptions.

Project completed in teams of two with clear role assignments.

Grading based on indentation, commenting, naming, snake mechanics, trophies, and overall gameplay.

📅 Milestones
Intermediate (due 11/25/2020):

Snake size 5 moving right, basic movement controls, visible border, no growth or trophies.

Final (due 12/07/2020):

Full game with all features including trophies and growth.

🛠️ How to Run
Compile the C source code using gcc with ncurses support:

bash
Copy
Edit
gcc -o snake snake.c -lncurses  
Run the game in a terminal:

bash
Copy
Edit
./snake  
📹 Submission Requirements
Single C source file with your implementation.

Short screencast (max 3 minutes) showing gameplay.
