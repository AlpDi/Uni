#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "convex_hull_alp.h"

void print_points(double x[], double y[], int N){
     
    for (int i = 0; i < N; i++){
        printf("%d. %lf %lf\n",i, x[i], y[i] );
    }
}

void read_points(int n, double x[], double y[]){
    for(int i = 0; i < n; i++){
        printf("x-Wert: \n");
        scanf("%lf", &x[i]);
        printf("y-Wert: \n");
        scanf("%lf", &y[i]);
    }
}


void rand_points(int n, double x[], double y[]){
    
    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < n; i++){
        x[i] = 20 * ( (1.0*rand() )/RAND_MAX) - 10;
        y[i] = 20 * ( (1.0*rand() )/RAND_MAX) - 10;    
    }
}


void display_corners(int m, double x[], double y[], int c[]){
    for(int i = 0; i < m; i++){
        printf("x: %lf y: %lf\n", x[c[i]], y[c[i]]);
    }
}


void switch_point(int n, double x[], double y[], int* i_start, int* i_switch ){
   
            
    int min = y[0];  
    int max = y[0];
    //returns index of min(y) and max(x)
    for (int i = 0; i < n; i++) {     
        if(y[i] < min){min = y[i]; *i_start = i;}
        if(y[i] > max){max = y[i]; *i_switch = i;}    
    }
}



int hull(int n, double x[], double y[], int c[]){

}
void plot_hull(int m, int n, double x[], double y[], int c[]);