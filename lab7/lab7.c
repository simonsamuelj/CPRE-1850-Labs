#include <stdio.h>
#include <stdlib.h>

#define MAXPOINTS 10000

// compute the average of the first num_items of buffer
double avg(double buffer[], int num_items);

// update the max and min of the first num_items of array
void maxmin(double array[], int num_items, double* max, double* min);


// shift length-1 elements of the buffer to the left and put the new_item on the right
void updatebuffer(double buffer[], int length, double new_item);

int main(int argc, char* argv[]) {
    double x, y, z;
    int Button_T, Button_C, Button_X, Button_S;
    int lengthofavg = 0;
    int count = 0;

    if (argc > 1) {
        sscanf(argv[1], "%d", &lengthofavg);
        printf("You entered a buffer length of %d\n", lengthofavg);
    } else {
        printf("Enter a length on the command line\n");
        return -1;
    }

    if (lengthofavg < 1 || lengthofavg > MAXPOINTS) {
        printf("Invalid length\n");
        return -1;
    }

    // Buffers for moving average
    double xbuf[lengthofavg];
    double ybuf[lengthofavg];
    double zbuf[lengthofavg];

    while (1) {
        scanf("%lf, %lf, %lf, %d, %d, %d, %d", &x, &y, &z, &Button_T, &Button_C, &Button_X, &Button_S);
        
        if(Button_S == 1) {
                break;
        }

        if (count < lengthofavg) {
            // fill up buffer until full
            xbuf[count] = x;
            ybuf[count] = y;
            zbuf[count] = z;
            count++;
        } 
        
        else {
            // shift and add new data point
            updatebuffer(xbuf, lengthofavg, x);
            updatebuffer(ybuf, lengthofavg, y);
            updatebuffer(zbuf, lengthofavg, z);

            // compute averages
            double xav = avg(xbuf, lengthofavg);
            double yav = avg(ybuf, lengthofavg);
            double zav = avg(zbuf, lengthofavg);

            // compute min and max
            double xmax, xmin, ymax, ymin, zmax, zmin;
            maxmin(xbuf, lengthofavg, &xmax, &xmin);
            maxmin(ybuf, lengthofavg, &ymax, &ymin);
            maxmin(zbuf, lengthofavg, &zmax, &zmin);

            // print values as CSV line
            printf("Value(x,y,z): %lf, %lf, %lf, Average(x,y,z): %lf, %lf, %lf\n", x, y, z, xav, yav, zav);
            fflush(stdout);
        }
    }

    return 0;
}

double avg(double buffer[], int num_items) {
    double sum = 0;
    for (int i = 0; i < num_items; i++) {
    sum += buffer[i];
    }
    return sum / num_items;
}

void maxmin(double array[], int num_items, double* max, double* min) {
    for (int i = 1; i < num_items; i++) {
        if (array[i] > *max) *max = array[i];
        if (array[i] < *min) *min = array[i];
    }
}

void updatebuffer(double buffer[], int length, double new_item) {
    for (int i = 0; i < length - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    buffer[length - 1] = new_item;
}

