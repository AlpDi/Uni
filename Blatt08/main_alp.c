#include "convex_hull_alp.h"
#include "libBMP.h"
#include <stdio.h>
#define N 10

#define WIDTH 1000
#define HEIGHT 1000

#define xMin -1.00
#define xMax  1.00
#define yMin -1.00
#define yMax  1.00

int toMath(int bmp_x, int bmp_y, double *x, double *y){
    *x = xMin + (bmp_x * (xMax - xMin)) / WIDTH;
    *y = yMin + ((HEIGHT - bmp_y) * (yMax - yMin) / HEIGHT);
}

int toBMP(double x, double y, int *bmp_x, int *bmp_y){
    *bmp_x=((x-xMin)*WIDTH)/(xMax-xMin);
    *bmp_y=HEIGHT-((y-yMin)*HEIGHT)/(yMax-yMin);
}

int main(void){
    int i_start = 0;
    int i_switch = 0;

    int grid = (int*)malloc(WIDTH * HEIGHT * sizeof(int));

    double x[N];
    double y[N];
    rand_points(N,x,y);
    print_points(x,y,N); 
    switch_point(N,y,x,&i_start,&i_switch);
    printf("%d %d\n", i_start, i_switch);
    
    
}