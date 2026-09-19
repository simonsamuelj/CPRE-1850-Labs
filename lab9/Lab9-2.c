#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#include <unistd.h> 
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 0   
#define COL_WIDTH 15   

int readWords(char* wl[MAXWORDS], char* filename);

void trimws(char* s);

void draw_character(int y, int x, char use);

void rowPlace(int index, int *row, int *column);


int main(int argc, char* argv[]) {
    char* wordlist[MAXWORDS];
    int wordCount, rowCount, extra;
    int i;
    int index = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s wordsfile\n", argv[0]);
        return 1;
    }

    wordCount = readWords(wordlist, argv[1]);
    rowCount = wordCount / 5;
    extra = wordCount % 5;
    int totalRows = (rowCount + (extra ? 1 : 0));
    int row, column;


    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE); 

    for (i = 0; i < wordCount; i++) {
        rowPlace(i, &row, &column);
        mvprintw(row, column, "%-15s", wordlist[i]);
    }
    refresh();

    int sel_r = 0;     
    int sel_c = 0;     
    int cursor_x = 0;  
    int cursor_y = 0;  

    rowPlace(0, &cursor_y, &cursor_x);
    cursor_x = cursor_x + COL_WIDTH;
    if (cursor_x < 0) cursor_x = 0;
    draw_character(cursor_y, cursor_x, '*');

    int k, num = 0;
    int time, b1, b2, b3, b4, j1_PRESS, j2_PRESS, j1_x, j1_y, j2_x, j2_y;
    int NA1, NA2, NA3, NA4, NA5, NA6;
    int timePrev = 0;
    int printWord = 0;

    int stringLengths[80];

    char *userString = malloc(sizeof(char) * 64);
    char *userSentence = malloc(sizeof(char) * 200);

    userString[0] = '\0';
    userSentence[0] = '\0';

    int sentenceRow = totalRows + 1;
    if (sentenceRow >= LINES - 1) sentenceRow = LINES - 2;

    while (1) {
        int inputs = scanf(" %d, %d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d, %d, %d, %d, %d",
              &time, &b1, &b2, &b3, &b4, &j1_PRESS, &j2_PRESS,
              &NA1, &NA2, &NA3, &NA4, &NA5, &NA6,
              &j1_x, &j1_y, &j2_x, &j2_y);

        if (inputs == 17 && (time - timePrev) >= 150) {

            draw_character(cursor_y, cursor_x, ' ');

            if ((j1_x < -60) && sel_c > 0) {
                sel_c--;
            }
            if ((j1_x > 60) && sel_c < 4 && (sel_r * 5 + sel_c + 1) < wordCount) {
                sel_c++;
            }
            if ((j1_y < -60) && sel_r > 0) {
                sel_r--;
                if ((sel_r * 5 + sel_c) >= wordCount) sel_c = (wordCount - 1) % 5;
            }
            if ((j1_y > 60) && sel_r < totalRows - 1) {
                sel_r++;
                if ((sel_r * 5 + sel_c) >= wordCount) sel_c = (wordCount - 1) % 5;
            }

            printWord = sel_r * 5 + sel_c;
            if (printWord < 0) printWord = 0;
            if (printWord >= wordCount) printWord = wordCount - 1;

            rowPlace(printWord, &cursor_y, &cursor_x);
            cursor_x -=2;
            if(cursor_x < 0){
                cursor_x = 0;
            }
            if (cursor_x < 0) cursor_x = 0;
            draw_character(cursor_y, cursor_x, '*');

            if (b1) {
                if ((int)strlen(userSentence + 0) < 80) {
                    strcpy(userString, " ");
                    strcat(userString, wordlist[printWord]);
                    stringLengths[num] = strlen(userString);
                    strcat(userSentence, userString);
                    mvprintw(sentenceRow, 5, "%-80s", " ");
                    mvprintw(sentenceRow, 5, "%s", userSentence);
                    num++;
                }
            }

            if (b4) {
                if ((int)strlen(userSentence) < 80) {
                    strcpy(userString, wordlist[printWord]);
                    stringLengths[num] = strlen(userString);
                    strcat(userSentence, userString);
                    mvprintw(sentenceRow, 5, "%-80s", " ");
                    mvprintw(sentenceRow, 5, "%s", userSentence);
                    num++;
                }
            }

            if (b3) {
                if (num > 0) {
                    int length = strlen(userSentence);
                    int removeLen = stringLengths[num - 1];
                    int newLen = length - removeLen;
                    if (newLen < 0) newLen = 0;
                    userSentence[newLen] = '\0';
                    num--;
                    mvprintw(sentenceRow, 5, "%-80s", " ");
                    mvprintw(sentenceRow, 5, "%s", userSentence);
                }
            }

            if (j2_PRESS) {
                mvprintw(sentenceRow, 5, "%-80s", " ");
                userSentence[0] = '\0';
                num = 0;
            }

            refresh();

            timePrev = time;
        }
        else {
            refresh();
            usleep(1000);
            continue;
        }
    }

    endwin();
    return 0;
}


int readWords(char* wl[MAXWORDS], char* filename) {
    char word[WORDLEN];
    int count = 0;
    FILE* f;
    f = fopen(filename, "r");

    if (!f) return 0;

    while (fscanf(f, "%s", word) == 1) {
        trimws(word);
        wl[count] = (char*)malloc(sizeof(char)*(strlen(word) + 1));
        strcpy(wl[count], word);
        count++;
    }
    fclose(f);
    return count;
}

void trimws(char* s) {
    int end = strlen(s) - 1;
    while (end >= 0 && isspace((unsigned char)s[end])) {
        s[end] = '\0';
        end--;
    }
}

void draw_character(int y, int x, char use) {
    mvaddch(y, x, use);
    refresh();
}

void rowPlace(int index, int *row, int *column) {
    *row = index / 5;
    *column = (((index % 5) * (WORDLEN + 4)) + 1);
}