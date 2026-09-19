/*----------------------------------------------------------------------------
-		        Lab 02 - Solving Simple Problems in C	    	 	 -
-	Name:																	 -
- 	Section:																 -
-	NetID:																     -
-	Date:																	 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    /* Put your code after this line */
	int a = 6427 + 1725;
	int b = (6971 * 3925) - 95;
	double c = 79 + 12 /5;
	double d = 3640.0 / 107.9;
	int e = (22 /3 ) * 3;
	int f = 22 / (3 * 3);
	double g = 22 / (3* 3); 
	double  h = 22 / 3* 3;
	double i = (22.0 /3) * 3.0;
	int j = 22.0 / (3*3.0);
	double k = 22.0 / 3.0 *3.0; 
	
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%lf\n", c);
	printf("%lf\n", d);
	printf("%d\n", e);
	printf("%d\n", f);
	printf("%lf\n", g);
	printf("%lf\n", h);
	printf("%lf\n", i);
	printf("%d\n", j);
	printf("%lf\n", k);
	
//area of circ w/ circumference of 23.567
	
	double area;
	double CIRCLE_CIRCUMFERENCE = 23.567;
	area = 2 * M_PI * CIRCLE_CIRCUMFERENCE;
	printf("Circle with %.2f circumference has an area of %.2f\n", CIRCLE_CIRCUMFERENCE, area);
	
	// convert 14ft to m
	double meterConversion;
	double FT_PER_METER = 3.28084;
	double feet = 14;
	meterConversion = FT_PER_METER * feet;
	printf("%.2f ft = %.2f m\n", feet, meterConversion);
   
   // Fareheit to Celicius
   double farenheit = 76;
   double celcius = (farenheit - 32)/1.8;
  printf("%.2f c = %.2f f", celcius, farenheit);
   return 0;
}
