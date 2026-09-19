/*-----------------------------------------------------------------------------
-					         SE/CprE 185 Lab 05 Part 2
-             DS4Drop with Air Resistance - Simon Samuel (simonsj1)
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define G 9.8                        // gravity contsant
#define WAIT_DOTS 10                 // print one '.' every this many lines
#define FALL_EXCLAMATIONS 10         // print one '!' every this many lines
#define FREEFALL_TOLERANCE 0.4       // tolerance for detecting ~0g
#define HIT_TOLERANCE 0.4            // tolerance for detecting hit (~1g)

// Function prototypes
double mag(double x, double y, double z);
int close_to(double tolerance, double point, double value);

int main(void) {
    char firstname[] = "Simon";
    char lastname[]  = "Samuel";
    char netid[]     = "simonsj1";

    double t, ax, ay, az;
    double a_mag;
    int count = 0;
    int falling = 0;
    double start_time = 0.0, end_time = 0.0;

    // Variables for air resistance model
    double t_prev = 0.0, v_prev = 0.0, x_prev = 0.0;

    printf("%s %s\n", firstname, lastname);
    printf("%s\n\n", netid);
    printf("Ok, I'm now receiving data.\n");
    printf("I'm Waiting ");

    while (scanf("%lf,%lf,%lf,%lf", &t, &ax, &ay, &az) == 4) {
        a_mag = mag(ax, ay, az);

        // If not yet falling
        if (!falling) {
            if (close_to(FREEFALL_TOLERANCE, 0.0, a_mag)) {
                falling = 1;
                start_time = t;
                t_prev = t; 
                printf("\n\nHelp me! I'm falling");
                count = 0;
            } else {
                if (count % WAIT_DOTS == 0)
                    printf(".");
                fflush(stdout);
            }
        }
        else { // falling
            double dt = (t - t_prev) / 1000.0; // convert ms to s

            // air resistance model
            double v = v_prev + G * (1 - a_mag) * dt;
            double x = x_prev + v * dt;

            // Check for landing
            if (close_to(HIT_TOLERANCE, 1.0, a_mag)) {
                end_time = t;
                double fall_time = (end_time - start_time) / 1000.0;
                double distance_no_resistance = 0.5 * G * fall_time * fall_time;

                printf("\n\nOuch! I fell %.3f meters in %.3f seconds.\n", distance_no_resistance, fall_time);
                printf("Compensating for air resistance, the fall was %.3f meters.\n", x);
                
                double percent_diff = ((distance_no_resistance - x) / distance_no_resistance) * 100.0;
                printf("This is %.1f%% less than computed before.\n", percent_diff);

                break;
            } else {
                if (count % FALL_EXCLAMATIONS == 0)
                    printf("!");
                fflush(stdout);
            }

            
            v_prev = v;
            x_prev = x;
            t_prev = t;
        }

        count++;
    }

    return 0;
}

double mag(double ax, double ay, double az) {
    return sqrt(ax * ax + ay * ay + az * az);
}

int close_to(double tolerance, double point, double value) {
    return fabs(point - value) < tolerance;
}
