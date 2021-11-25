#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "libBMP.h"

#define WIDTH 1000
#define HEIGHT 1000
#define GRID_HALF 1000/2


#define xMin -10.00
#define xMax  10.00
#define yMin -10.00
#define yMax  10.00

int toMath(int bmp_x, int bmp_y, double *x, double *y){
    *x = xMin + (bmp_x * (xMax - xMin)) / WIDTH;
    *y = yMin + ((HEIGHT - bmp_y) * (yMax - yMin) / HEIGHT);
}

int toBMP(double x, double y, int *bmp_x, int *bmp_y){
    *bmp_x=((x-xMin)*WIDTH)/(xMax-xMin);
    *bmp_y=HEIGHT-((y-yMin)*HEIGHT)/(yMax-yMin);
}


int main(void){
    
    int Gx, Gy;
    double x,y;

    uint32_t *grid = (uint32_t*)malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    for(int i = 0; i <= HEIGHT * WIDTH; i++){
        grid[i] = COLOR_WHITE;
    }

    toBMP(0.0, 0.0, &Gx, &Gy);
    for(int bmp_x = 0, bmp_y; bmp_x < WIDTH; bmp_x++, bmp_y++){
        grid[Gy * WIDTH + bmp_x] = COLOR_BLACK;
        grid[bmp_y * HEIGHT + Gx] = COLOR_BLACK;
    }

    bmp_create("ex1.bmp", grid, WIDTH, HEIGHT);
}

