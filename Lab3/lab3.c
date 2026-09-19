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


int main(void) {
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    int t;
    double  ax, ay, az;     


    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
        scanf("%d,%lf,%lf,%lf", &t, &ax, &ay, &az);

/* CODE SECTION 0 
        double seconds = t / 1000.0;
        printf("Echoing output: %8.3f, %7.4f, %7.4f, %7.4f\n", seconds, ax, ay, az);  */

/* CODE SECTION 1 */
        /* printf("At %d ms, the acceleration's magnitude was: %lf\n", 
            t, mag(ax, ay, az)); */ 
            
/* CODE SECTION 2 */
        printf("At %d minutes, %d seconds, and %d milliseconds it was: %lf\n", 
        minutes(t), seconds(t), millis(t), mag(ax,ay,az)); 

    }

return 0;
}

/* Put your functions here */
