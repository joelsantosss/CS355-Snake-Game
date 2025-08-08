// Authors: Joel Santos & Michael Balachandar

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <ncurses.h>
#include <string.h>

#define BORDER_CHAR ACS_DIAMOND      // set BORDER char to diamond

int playerScore = 0;                 // player score
int currentDirection = 4;            // initial direction
bool isGameOverFlag = false;         // flag for game status
time_t trophyStartTime;             // Time when the trophy was placed
int trophyDuration;                 // Random duration for trophy expiration

//snake struct
struct bodySegment {
    int x;
    int y;
    char value; // To store the trophy digit (if needed for apple)
};


struct playerSnake {
    int size;                         // size of snake
    struct bodySegment segments[256]; 
};

struct playerSnake snake;  
struct bodySegment apple;  

// function prototypes so the compiler won't (comp)lain
void updateBoard();
void initializeBorder();
void startGame();
void displayScore();
void movePlayerSnake();
bool checkIfGameOver();
void gameOverScreen();
void placeTrophy();
void drawTrophy();


int main() {
    // written by: Joel Santos & Michael Balachandar
    // entry point of game makes screen, sets color pairs, and starts game
    
    srand(time(NULL));             //seed random number gen
    initscr();                     //initialize curses lib
    
    start_color();                 // start using color
    use_default_colors();          // use terminal default color for BG
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA); // the border char color is white and the char backround is magenta
    init_pair(2, COLOR_GREEN, -1);      // snake color
    init_pair(3, COLOR_RED, -1);        // end screen color
    init_pair(4, COLOR_YELLOW, -1);         // trophy color
    init_pair(5, COLOR_WHITE    , COLOR_GREEN);   // score color
    
    startGame();                   // start game loop
    gameOverScreen();
    endwin();                      // end curses
    
    return 0;
}

void movePlayerSnake() {  
    // written by: Joel Santos
    // updates snake position in player snake struct and sends to board to update position               
    
    int deltaX = 0;        // change in x
    int deltaY = 0;        // change in y

    //direction of movement
    switch (currentDirection) {
        case 1: deltaX = -1; break; // up
        case 2: deltaX = 1; break;  // down
        case 3: deltaY = -1; break; // left
        case 4: deltaY = 1; break;  // right
    }

    //move snake body
    for (int i = snake.size - 1; i > 0; i--) {
        snake.segments[i] = snake.segments[i - 1];
    }
    
    //move snake head
    snake.segments[0].x += deltaX;
    snake.segments[0].y += deltaY;

    if (snake.segments[0].x < 0) snake.segments[0].x = LINES - 1;
    if (snake.segments[0].x >= LINES) snake.segments[0].x = 0;
    if (snake.segments[0].y < 0) snake.segments[0].y = COLS - 1;
    if (snake.segments[0].y >= COLS) snake.segments[0].y = 0;

    if (snake.segments[0].x == apple.x && snake.segments[0].y == apple.y) {
        playerScore += apple.value - '0'; // Convert the char value to its numeric value
        snake.size += apple.value - '0';    // Grow the snake
        placeTrophy();       // Place a new apple
        displayScore();     // Update the score display
    }

    updateBoard();              // update board with new snake position
}

void startGame() {
    // written by: Joel Santos
    // starts game by reseting score, clearing screen, 
    // initalizes screen properties, initializes snake, controls snake position
    
    int game_speed = 12;        // sets game speed
    playerScore = 0;            // reset score
    isGameOverFlag = false;     // reset game end flag
    
    clear();                    // clear screen
    curs_set(0);                // hide cursor
    noecho();                   // disable echo
    nodelay(stdscr, TRUE);  
    keypad(stdscr, TRUE);       // allow arrow keys
    
    initializeBorder();         // initialize border
    placeTrophy();
                                // initialize snake head
    snake.size = 5;             // starting size
    snake.segments[0].x = 10;   // initialize snake head position
    snake.segments[0].y = 10;   

    //initialize snake body
    for (int i = 0; i < snake.size; i++) {
        snake.segments[i].x = 10;       
        snake.segments[i].y = 10 - i;
    }

    updateBoard();               // initial render board

    // game loop
    while (!isGameOverFlag) {
        int ch = getch();                                                           // user input
        switch (ch) {
            case 'q': isGameOverFlag = true; break;                                 // quit
            case KEY_UP: if (currentDirection != 2) currentDirection = 1; break;    // change direction
            case KEY_DOWN: if (currentDirection != 1) currentDirection = 2; break;
            case KEY_LEFT: if (currentDirection != 4) currentDirection = 3; break;
            case KEY_RIGHT: if (currentDirection != 3) currentDirection = 4; break;
        }

        movePlayerSnake();        
        isGameOverFlag = checkIfGameOver();
        usleep(1000000/game_speed);
    }

    keypad(stdscr, FALSE);
    currentDirection = 0;
    sleep(1);
}

void initializeBorder() {
    // written by: Michael Balachandar
    // initializes border for game start using animation and color because it's cool
    // prints it in O(log(n)) time while making it look like 
    // all borders are printed at same time  

    attron(COLOR_PAIR(1)); // set border BG magenta and white char color 
    int colCursor = 1;
    int lineCursor = 0;
    int animate_speed = 75;
    curs_set(0);
    while (colCursor < COLS || lineCursor < LINES) {
        if (colCursor < COLS && lineCursor < LINES) { 
            if (colCursor % 2 == 0) {                                    // makes top and bottom border have similar spacing like left and right borders
                mvaddch(0, colCursor, BORDER_CHAR);                      // top border print
                mvaddch(LINES - 1, COLS - (colCursor + 1), BORDER_CHAR); // bottom border print in reverse
            }
            else {
                mvaddch(0, colCursor, ' ');                              // top border print
                mvaddch(LINES - 1, COLS - (colCursor + 1), ' ');         // bottom border print in reverse
            }

            mvaddch(lineCursor, 0, BORDER_CHAR);                         // left border print
            mvaddch(LINES - lineCursor, COLS - 1 , BORDER_CHAR);         // left border print in reverse    
        }

        // continue printing left and right border if top and bottom borders are done printing
        else if (lineCursor < LINES - 1) {  
            mvaddch(lineCursor, 0, BORDER_CHAR);
            mvaddch(LINES - lineCursor, COLS, BORDER_CHAR);
        }

        // finish printing top and bottom border if left and right borders are done printing
        else{
            if (colCursor % 2 == 0) { 
                mvaddch(0, colCursor, BORDER_CHAR);                     // top border print
                mvaddch(LINES - 1, COLS - (colCursor+1), BORDER_CHAR);  // bottom border print in reverse
            }
            else {
                mvaddch(0, colCursor, ' ');                             // top border print
                mvaddch(LINES - 1, COLS - (colCursor+1), ' ');          // bottom border print in reverse
            }
        }
        
        colCursor++;                                                    // increments line and column cursor
        lineCursor++;

        refresh();                                                      // refresh screen on each iteration to produce animation
        usleep(1000000/animate_speed);                                  // speed of animation
    }
    attroff(COLOR_PAIR(1));                                             // stops border color pair from affecting snake color
    
}
void draw_border() {
    // written by: Michael Balachandar
    // redraws border for when screen refreshes for snake position updates without animation
    // basically same function as initialize_border but with no screen refreshes

    attron(COLOR_PAIR(1));                                              // set border BG magenta and white char color 
    int colCursor = 1;
    int lineCursor = 0;
    while (colCursor < COLS || lineCursor < LINES) {
        if (colCursor < COLS && lineCursor < LINES) {
            if (colCursor % 2 == 0) {
                mvaddch(0, colCursor, BORDER_CHAR);                      // top border print
                mvaddch(LINES - 1, COLS - (colCursor + 1), BORDER_CHAR); // bottom border print in reverse
            }
            else {
                mvaddch(0, colCursor, ' ');                              // top border print
                mvaddch(LINES - 1, COLS - (colCursor + 1), ' ');         // bottom border print in reverse
            }

            mvaddch(lineCursor, 0, BORDER_CHAR);                         // left border print
            mvaddch(LINES - lineCursor, COLS - 1 , BORDER_CHAR);         // left border print in reverse    
        } 

        // continue printing left and right border if top and bottom borders are done printing
        else if (lineCursor < LINES - 1) {
            mvaddch(lineCursor, 0, BORDER_CHAR);
            mvaddch(LINES - lineCursor, COLS, BORDER_CHAR);
        }

        // finish printing top and bottom border if left and right borders are done printing
        else{
            if (colCursor % 2 == 0) {
                mvaddch(0, colCursor, BORDER_CHAR);                     // top border print
                mvaddch(LINES - 1, COLS - (colCursor+1), BORDER_CHAR);  // bottom border print in reverse
            }
            else {
                mvaddch(0, colCursor, ' ');                             // top border print
                mvaddch(LINES - 1, COLS - (colCursor+1), ' ');          // bottom border print in reverse
            }
        }
        
        colCursor++;
        lineCursor++;
    }
    attroff(COLOR_PAIR(1));
}

void placeTrophy() {
    // written by: Michael Balachandar
    // generates trophy position and value
    bool validPosition = false;

    while (!validPosition) {
        // Generate random position within the screen, inside the border
        int x = rand() % (LINES - 2) + 1; // rows between 1 and LINES-2
        int y = rand() % (COLS - 2) + 1; // columns between 1 and COLS-2

        // generate a random digit between 1 and 9 for the trophy
        char trophyValue = '1' + (rand() % 9); // random digit as a character

        // check if the trophy's position overlaps with the snake
        validPosition = true;
        for (int i = 0; i < snake.size; i++) {
            if (snake.segments[i].x == x && snake.segments[i].y == y) {
                validPosition = false; // overlaps with snake find new one
                break;
            }
        }

        // If valid position is found, place the trophy
        if (validPosition) {
            apple.x = x;
            apple.y = y;
            apple.value = trophyValue; // assign the trophy value
            mvaddch(apple.x, apple.y, apple.value); // display trophy
            refresh();

            // expiration timer
            trophyStartTime = time(NULL);          // current time
            trophyDuration = 1 + rand() % 9;       // random duration (1-9 seconds)
        }
    }
}

void drawTrophy() {
    // written by: Michael Balachandar
    // redraw trophy for screen refresh
    attron(COLOR_PAIR(4));
    mvaddch(apple.x, apple.y, apple.value); // Use the trophy's value
    attroff(COLOR_PAIR(4));
}

void checkTrophyCollision() {
    // Check if the snake's head overlaps with the trophy's position
    if (snake.segments[0].x == apple.x && snake.segments[0].y == apple.y) {
        // Convert trophy value (char) to integer and add to playerScore
        playerScore += apple.value - '0'; // Convert char ('1'-'9') to int (1-9)

        // Place a new trophy at a valid position
        placeTrophy();
    }
}

void updateTrophyState() {
    // Check if the trophy has expired
    if (time(NULL) - trophyStartTime >= trophyDuration) {
        // Trophy has expired, place a new one
        placeTrophy();
    }
}


void updateBoard() {
    // written by: Michael Balachandar
    // updates game screen by erasing and refreshing with new snake position
    // redraws border and adjusts the snake's head based on direction snake is facing

    char head;
    erase();                    // erase game window for rendering of the snake's position
    
    switch (currentDirection) { // decides the head char based on direction
        case 1: head = '^'; 
            break;
        case 2: head = 'v';
            break;
        case 3: head = '<';
            break;
        case 4: head = '>';
            break;
    }

    draw_border();                               // redraw border
    attron(COLOR_PAIR(2));                       // set snake to color green
    for (int i = 0; i < snake.size; i++) { 
        if (i == 0) {
            mvaddch(snake.segments[i].x, snake.segments[i].y, head);      // pick head segment
        }
        else {
            mvaddch(snake.segments[i].x, snake.segments[i].y, ACS_BLOCK); // body segment
        }
    }
    attroff(COLOR_PAIR(2));         // sets color green to snake only
    displayScore();
    drawTrophy();
    checkTrophyCollision();
    updateTrophyState();    // Check and handle trophy expiration
    refresh();                      // refresh screen with new snake position
}

void displayScore() {
    // written by: Michael Balachandar
    // display the player score in the center of the top border
    int centerX = COLS / 2;     // calculate the horizontal center of the screen
    char scoreText[50];

    // format the score text
    snprintf(scoreText, sizeof(scoreText), " Score: %d ", playerScore);

    // clear the area where the score is displayed
    mvprintw(0, centerX - strlen(scoreText) / 2, "              "); 

    // display the score centered at the top border
    attron(COLOR_PAIR(5)); // green and white for score
    mvprintw(0, centerX - strlen(scoreText) / 2, "%s", scoreText); // print the score
    attroff(COLOR_PAIR(5)); 
}

bool checkIfGameOver() {
    // written by: Joel Santos
    // checks if the snake hits its self and ends game
    int headX = snake.segments[0].x;
    int headY = snake.segments[0].y;

    //check if head collides with body
    for (int i = 1; i < snake.size; i++) {
        if (snake.segments[i].x == headX && snake.segments[i].y == headY) {
            return true;    //game over
        }
    }
    if (headX <= 0 || headX >= LINES - 1 || headY <= 0 || headY >= COLS - 1) {
        return true;  // game over
    }
    return false;
}

void gameOverScreen() {
    // writen by: Michael Balachandar
    // http://patorjk.com/software/taag/ (art generator used) 
    // makes ascii art in red flash 
    char *game_over_art[] = {   
        "   _____                         ____                 ",
        "  / ____|                       / __ \\                ",
        " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ ",
        " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|",
        " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   ",
        "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   ",
    };
    int art_lines = sizeof(game_over_art) / sizeof(game_over_art[0]);   // gets the number of lines required to print
    int art_cols = 0;                                                   

    // find the max line length for 
    for (int i = 0; i < art_lines; i++) {
        int len = strlen(game_over_art[i]);
        if (len > art_cols) {
            art_cols = len;
        }
    }

    // get starting position to center so its centered
    int start_y = (LINES - art_lines) / 2;
    int start_x = (COLS - art_cols) / 2;

    int flashes = 4;            // number of times to flash the message
    
    
    for (int i = 0; i < flashes; i++) { // makes it look like flashing 
        clear();                // clear game 
        displayScore();         // diplay score
        attron(COLOR_PAIR(3));      // set color to red
        if (i % 2 == 0) {
            // prints line by line for animation
            for (int j = 0; j < art_lines; j++) {
                mvprintw(start_y + j, start_x, "%s", game_over_art[j]);
                refresh();
                usleep(1000000/25); 
            }
        }
        
        refresh();
        usleep(1000000/10);
        
    }

    // display the game over one more time
    clear();
    displayScore();
    attron(COLOR_PAIR(3));
    for (int j = 0; j < art_lines; j++) {
        mvprintw(start_y + j, start_x, "%s", game_over_art[j]);
    }
    refresh();
    attroff(COLOR_PAIR(3)); 
    sleep(1); // sleep for smoother transition
}
