355 Snake Game
Classic Snake game implemented in C for the CS 355 Systems Programming course (Fall 2020).

🐍 Project Overview
This project implements the classic Snake game playable in the terminal using the ncurses library. The snake moves inside a bordered “snake pit” area, growing by eating numbered trophies that appear randomly. The game features increasing speed, trophy expiration, and strict gameplay rules.

🎮 Key Features
🕹️ Snake Movement & Growth
Initial snake length of 3 characters.

Starts moving in a random direction.

Controlled using arrow keys (no reversing).

Speed increases as snake grows.

🎯 Trophies
One trophy visible at all times, represented by a digit 1–9.

Eating a trophy increases snake length by that number.

Trophies expire after 1–9 seconds and respawn randomly.

⚠️ Gameplay Rules
Game ends if snake hits the border or itself.

Game ends if user tries to reverse direction.

Player wins when snake length reaches half the border’s perimeter.

📅 Course Requirements & Milestones
Intermediate Deliverable (due 11/25/2020):

Snake of size 5 moving right.

Movement in all directions enabled.

Visible snake pit border.

No growth or trophies.

Final Deliverable (due 12/07/2020):

Full implementation with trophies, growth, and all gameplay rules.

🛠️ Technologies Used
Programming Language: C

Library: ncurses for terminal UI

Development Environment: Linux terminal (e.g., Google Cloud Console)

⚙️ How to Run
Compile the source code with ncurses support:

bash
Copy
Edit
gcc -o snake snake.c -lncurses  
Run the game in your terminal:

bash
Copy
Edit
./snake  
📹 Submission Requirements
Submit a single C source file (snake.c) containing your code.

Provide a short video screencast (max 3 minutes) demonstrating gameplay.
