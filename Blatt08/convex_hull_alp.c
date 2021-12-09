#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "convex_hull_alp.h"

void read_points(int n, double x[], double y[]){
    for(int i = 0; i < n; i++){
        printf("x-Wert: \n");
        scanf("%lf", &x[i]);
        printf("y-Wert: \n");
        scanf("%lf", &y[i]);
    }
}






void rand_points(int n, double x[], double y[]){

    for(int i = 0; i < n; i++){
        x[i] = 20 * ( (1.0*rand() )/RAND_MAX) - 10;
        y[i] = 20 * ( (1.0*rand() )/RAND_MAX) - 10;    
    }
}


void display_corners(int m, double x[], double y[], int c[]);
void switch_point(int n, double x[], double y[], int* i_start, int* i_switch );
int hull(int n, double x[], double y[], int c[]);
void plot_hull(int m, int n, double x[], double y[], int c[]);