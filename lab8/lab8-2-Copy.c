#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>

#define NUMCOLS 100
#define NUMROWS 72

#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

char MAZE[NUMROWS][NUMCOLS];

// Prototypes
void generate_maze(int difficulty);
void draw_maze(void);
void draw_character(int x, int y, char use);


int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: ./lab8 difficulty\n");
        return 1;
    }

    int difficulty = atoi(argv[1]);

    // Ncurses setup
    initscr();
    noecho();
    curs_set(0);
    refresh();

    // Maze generation
    generate_maze(difficulty);
    draw_maze();

    // Avatar starting position
    int x = COLS / 2;
    int y = 0;
    draw_character(x, y, AVATAR);

    // DS4 variables
    double t, gx, gy, gz;
    int T_btn, C_btn, X_btn, S_btn;

    // Timing for fall
    double prevFallTime = 0;
    int FALL_DELAY = 300; 

    // Tilt sensitivity
    double tolerance = 0.5;

    
    // GAME LOOP
    
    while (1)
    {
        // Read 8 values from ds4rd
        if (scanf("%lf,%lf,%lf,%lf,%d,%d,%d,%d",
            &t, &gx, &gy, &gz,
            &T_btn, &C_btn, &X_btn, &S_btn) != 8)
        {
            continue;
        }

        
        // LEFT MOVEMENT
        if (gx > tolerance)
        {
            if (x > 0 && MAZE[y][x - 1] == EMPTY_SPACE)
            {
                draw_character(x, y, ' ');
                x--;
                draw_character(x, y, AVATAR);
            }
        }

        
        // RIGHT MOVEMENT
        if (gx < -tolerance)
        {
            if (x < COLS - 1 && MAZE[y][x + 1] == EMPTY_SPACE)
            {
                draw_character(x, y, ' ');
                x++;
                draw_character(x, y, AVATAR);
            }
        }

        
        // FALLING
        if ((t - prevFallTime) > FALL_DELAY)
        {
            if (y < LINES - 1 && MAZE[y + 1][x] == EMPTY_SPACE)
            {
                draw_character(x, y, ' ');
                y++;
                draw_character(x, y, AVATAR);
            }
            prevFallTime = t;
        }

        
        // WIN CONDITION
        if (y >= LINES - 1)
        {
            endwin();
            printf("YOU WIN!\n");
            return 0;
        }

        
        // BONUS 1
        int canMoveLeft  = (x > 0          && MAZE[y][x - 1] == EMPTY_SPACE);
        int canMoveRight = (x < COLS - 1   && MAZE[y][x + 1] == EMPTY_SPACE);
        int canMoveDown  = (y < LINES - 1  && MAZE[y + 1][x] == EMPTY_SPACE);

        if (!canMoveLeft && !canMoveRight && !canMoveDown)
        {
            endwin();
            printf("YOU LOSE - You got stuck!\n");
            return 0;
        }
    }

    endwin();
    return 0;
}


// Maze creation

void generate_maze(int difficulty)
{
    for (int r = 0; r < NUMROWS; r++)
    {
        for (int c = 0; c < NUMCOLS; c++)
        {
            if (rand() % 100 < difficulty)
                MAZE[r][c] = WALL;
            else
                MAZE[r][c] = EMPTY_SPACE;
        }
    }
}


// Draw maze

void draw_maze(void)
{
    for (int r = 0; r < LINES; r++)
        for (int c = 0; c < COLS; c++)
            mvaddch(r, c, MAZE[r][c]);

    refresh();
}


// Provided: DO NOT MODIFY

void draw_character(int x, int y, char use)
{
    mvaddch(y, x, use);
    refresh();
}
