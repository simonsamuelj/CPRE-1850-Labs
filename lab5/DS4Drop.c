/*-----------------------------------------------------------------------------
-					         SE/CprE 185 Lab 04
-             Developed for 185-Rursch by T.Tran and K.Wang
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-	                            Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>


/*-----------------------------------------------------------------------------
-	                            Defines
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/
double mag(double x, double y, double z);
int close_to(double tolerance, double point, double value);

/*-----------------------------------------------------------------------------
-							  Implementation
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define G 9.8                        // gravity constant
#define WAIT_DOTS 10                 // print one '.' every this many lines
#define FALL_EXCLAMATIONS 10         // print one '!' every this many lines
#define FREEFALL_TOLERANCE 0.5       // tolerance for detecting ~0g
#define HIT_TOLERANCE 0.5            // tolerance for detecting hit (~1g)

int main(void) {
    char firstname[] = "Simon";     
    char lastname[]  = "Samuel";      
    char netid[]     = "simonsj1";    

    double t, ax, ay, az;
    double a_mag;
    int count = 0;
    int falling = 0;
    double start_time = 0.0, end_time = 0.0;

    printf("%s %s\n", firstname, lastname);
    printf("%s\n\n", netid);
    printf("Ok, I'm now receiving data.\n");
    printf("I'm Waiting ");

    
    while (scanf("%lf,%lf,%lf,%lf", &t, &ax, &ay, &az) == 4) {
        a_mag = mag(ax, ay, az);

        // If not falling yet
        if (!falling) {
            if (close_to(FREEFALL_TOLERANCE, 0.0, a_mag)) {
                // start of freefall
                falling = 1;
                start_time = t;
                printf("\n\nHelp me! I'm falling");
                count = 0;
            } else {
                // still waiting
                if (count % WAIT_DOTS == 0)
                    printf(".");
                fflush(stdout);
            }
        }
        else { // falling == 1
            if (close_to(HIT_TOLERANCE, 1.0, a_mag)) {
                // end of fall
                end_time = t;
                double fall_time = end_time - start_time;
                fall_time = fall_time / 1000;
                double distance = 0.5 * G * fall_time * fall_time;
                printf("\n\nOuch! I fell %.3f meters in %.3f seconds.\n", distance, fall_time);
                break;
            } else {
                if (count % FALL_EXCLAMATIONS == 0)
                    printf("!");
                fflush(stdout);
            }
            
        }
        count++;
    }

    return 0;
}


double mag(double ax, double ay, double az) {
    return sqrt(ax*ax + ay*ay + az*az);
}

int close_to(double tolerance, double point, double value) {
    return fabs(point - value) < tolerance;
}
