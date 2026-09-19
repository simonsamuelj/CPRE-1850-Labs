// 185 lab6.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when the square button is pressed
//  False Otherwise
//This function is the ONLY place scanf is allowed to be used
//POST: it modifies its arguments to return values read from the input line.
int read_line(double* g_x, double* g_y, double* g_z, int* Button_T, int* Button_C, int* Button_X, int* Button_S);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

int main() {
    double x, y, z;
    int time, b_Triangle, b_X, b_Square, b_Circle;
    double roll_rad, pitch_rad;
    int scaled_value;
    int mode = 0; // 0 = roll, 1 = pitch
    int counter = 0;
    
    while (read_line(&x, &y, &z, &b_Triangle, &b_Circle, &b_X, &b_Square)) {
        if (b_Triangle) {
            counter++;
            if(counter % 2 == 0) {
                mode = 0;
            }
            else {
                mode = 1;
            }
        }
        if (b_Square) break;
        
        if (mode == 0)
            roll_rad = roll(x), scaled_value = scaleRadsForScreen(roll_rad);
        else
            pitch_rad = pitch(z), scaled_value = scaleRadsForScreen(pitch_rad);

        graph_line(scaled_value);
        fflush(stdout);
    }

    return 0;
}

int read_line(double* g_x, double* g_y, double* g_z, int* Button_T, int* Button_C, int* Button_X, int* Button_S) {
	 int result = scanf("%lf,%lf,%lf,%d,%d,%d,%d,%d", g_x, g_y, g_z, Button_T, Button_C, Button_X, Button_S);
}

double roll(double x_mag) {
    if (x_mag > 1.0) x_mag = 1.0;
    if (x_mag < -1.0) x_mag = -1.0;
    return asin(x_mag);
}

double pitch(double y_mag) {
    if (y_mag > 1.0) y_mag = 1.0;
    if (y_mag < -1.0) y_mag = -1.0;
    return asin(y_mag);
}
 
int scaleRadsForScreen(double rad) {
    // Map [-PI/2, PI/2] → [-39, 39]
    double scale = 39.0 / (PI / 2.0);
    return (int)(rad * scale);
}

void print_chars(int num, char use) {
    for (int i = 0; i < num; i++) {
        printf("%c", use);
    }
}

void graph_line(int number) {
    if (number == 0) {
        print_chars(39, ' ');
        printf("0\n");
    } else if (number > 0) {
        print_chars(39, ' ');
        printf("0");
        print_chars(number, 'r');
        printf("\n");
    } else { // number < 0
        print_chars(39 + number, ' ');
        print_chars(-number, 'l');
        printf("0\n");
    }
}

