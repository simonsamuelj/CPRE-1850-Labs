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

// Function prototypes
void generate_maze(int difficulty);
void draw_maze(void);
void draw_character(int x, int y, char use);
float calc_roll(float x_mag);

// MAIN
int main(int argc, char* argv[])
{
    if (argc < 2) { 
        printf("Usage: ./lab8 difficulty\n");
        return 1;
    }

    int difficulty = atoi(argv[1]); // difficulty = % chance of WALL

    // Ncurses setup
    initscr();
    noecho();
    curs_set(0);
    refresh();

    // Generate and draw maze
    generate_maze(difficulty);
    draw_maze();

    // Initial avatar position (top middle)
    int x = COLS / 2;
    int y = 0;
    draw_character(x, y, AVATAR);

    int delay = 100; // milliseconds between falls (adjust as needed)

    // GAME LOOP: avatar falls down each frame
    while (y < LINES - 1)
    {
        usleep(delay * 1000);

        // Erase avatar from old spot
        draw_character(x, y, ' ');

        // Move down if next spot isn't a wall
        if (MAZE[y + 1][x] == EMPTY_SPACE)
            y++;

        draw_character(x, y, AVATAR);
    }

    endwin();
    printf("YOU WIN!\n");
    return 0;
}

// Create random maze based on difficulty %
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

// Print maze with mvaddch
void draw_maze(void)
{
    for (int r = 0; r < LINES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            mvaddch(r, c, MAZE[r][c]);
        }
    }
    refresh();
}

// Provided — DO NOT MODIFY
void draw_character(int x, int y, char use)
{
    mvaddch(y, x, use);
    refresh();
}

float calc_roll(float x_mag)
{
    // placeholder for now — will use DS4 input in Part 2
    return x_mag;
}



