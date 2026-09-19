/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>

/* Put your function prototypes here */
double mag(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}
int minutes(int t) {
    return t / 60000;
}
int seconds(int t) {
    return (t / 1000) % 60;
}
int millis(int t) {
    return t % 1000;
}

/* -------- NEW PURE FUNCTION for Part 4 (no scanf/printf here) -------- */
int count_pressed(int triangle, int circle, int cross, int square) {
    return (triangle != 0) + (circle != 0) + (cross != 0) + (square != 0);
}

int main(void) {
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    int t;
    double ax, ay, az;

    /* -------- NEW VARIABLES for Part 4 -------- */
    int tri, cir, cro, squ;  /* triangle, circle, cross, square */

    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
        if (scanf("%d,%d,%d,%d", &tri, &cir, &cro, &squ) != 4) {
            continue;
        }
        
        printf("%d\n", count_pressed(tri, cir, cro, squ));
        fflush(stdout);
    }

    return 0;
}

/* Put your functions here */

