// Lab 9 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 1   // set to 0 to disable debug output

// reads words from the file
// into wl and trims the whitespace off of the end of each word
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
void trimws(char* s);

int main(int argc, char* argv[]) {
    char* wordlist[MAXWORDS];
    int wordCount;
    int i;

    // Check for filename
    if (argc < 2) {
        printf("ERROR: Provide a filename as a command line argument.\n");
        return 1;
    }

    // Read words using readWords()
    wordCount = readWords(wordlist, argv[1]);

    if (DEBUG) {
        printf("Read %d words from %s \n", wordCount, argv[1]);

        // 🔹 PART 1 REQUIREMENT: Print all words to the screen
        for (i = 0; i < wordCount; i++) {
            printf("%s\n", wordlist[i]);
        }
    }

    return 0;
}

// ----------------------------------------------------------
// Function: readWords()
// Uses fgets() to read each line, trims whitespace, stores words
// ----------------------------------------------------------
int readWords(char* wl[MAXWORDS], char* filename) {
    FILE *fp;
    char buffer[WORDLEN + 2];  // +2 allows room for newline and null char
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ERROR: Could not open file %s\n", filename);
        return 0;
    }

    // Read each line using fgets()
    while (fgets(buffer, sizeof(buffer), fp) != NULL && count < MAXWORDS) {
        trimws(buffer);                     // remove trailing whitespace
        wl[count] = strdup(buffer);         // store word in memory
        count++;
    }

    fclose(fp);
    return count;
}

// ----------------------------------------------------------
// Function: trimws()
// removes whitespace from the RIGHT side of the string
// ----------------------------------------------------------
void trimws(char* s) {
    int len = strlen(s);

    // Move from end until a non-space character is found
    while (len > 0 && isspace(s[len - 1])) {
        len--;
    }
    s[len] = '\0';  // End string at new position
}
