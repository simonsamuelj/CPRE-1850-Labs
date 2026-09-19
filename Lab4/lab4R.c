/*-----------------------------------------------------------------------------
-                         SE/CprE 185 Lab 04 – Conditionals
-   Starter fixed & completed with movement/orientation logic and features.
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <string.h>

/*-----------------------------------------------------------------------------
-                               Prototypes
-----------------------------------------------------------------------------*/
double mag(double x, double y, double z);
int    close_to(double tolerance, double point, double value);
const char* orientation_from_g(double gx, double gy, double gz, double g_tol);

/*-----------------------------------------------------------------------------
-                               Config
-----------------------------------------------------------------------------*/

static const double MOV_TOL = 0.15;
static const double G_TOL = 0.25;`

#define TRIANGLE_PRESSED(b1) ((b1) != 0)

/*-----------------------------------------------------------------------------
-                            Implementation
-----------------------------------------------------------------------------*/
int main(void) {
    int t, b1, b2, b3, b4;
    double ax, ay, az, gx, gy, gz;

    const char* last_printed = "";

    while (1) {
        if (scanf("%d, %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
                  &t, &ax, &ay, &az, &gx, &gy, &gz, &b1, &b2, &b3, &b4) != 11) {
            break;
        }

        double a_mag = mag(ax, ay, az);
        int is_still = close_to(MOV_TOL, 0.0, a_mag);

        if (TRIANGLE_PRESSED(b1)) {
            break;
        }

        if (is_still) {
            const char* ori = orientation_from_g(gx, gy, gz, G_TOL);
            if (ori && strcmp(ori, last_printed) != 0) {
                printf("%s\n", ori);
                last_printed = ori;
            }
        }
    }
    return 0;
}

/*-----------------------------------------------------------------------------
-                           Helper Functions
-----------------------------------------------------------------------------*/
double mag(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}

int close_to(double tolerance, double point, double value) {
    return fabs(value - point) <= tolerance;
}

const char* orientation_from_g(double gx, double gy, double gz, double g_tol) {
    double ax = fabs(gx), ay = fabs(gy), az = fabs(gz);

    if (ax >= ay && ax >= az) {
        if (close_to(g_tol,  1.0,  ax)) {
            return (gx > 0) ? "RIGHT" : "LEFT";
        }
    } else if (ay >= ax && ay >= az) {
        if (close_to(g_tol,  1.0,  ay)) {
            return (gy > 0) ? "FRONT" : "BACK";
        }
    } else { 
        if (close_to(g_tol,  1.0,  az)) {
            return (gz > 0) ? "BOTTOM" : "TOP";
        }
    }
    return NULL;
}

