#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "libBMP.h"

#define WIDTH 1000
#define HEIGHT 1000
#define GRID_HALF 1000/2


#define xMin -1.00
#define xMax  1.00
#define yMin -1.00
#define yMax  1.00

float u(float k, float r){
    return k/(1+k*(1-k)*r);
}

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

    for(int bmp_x = 0; bmp_x < WIDTH; bmp_x++){
        toMath(bmp_x, 0, &x, &y);
        toBMP(x, sin(x), &Gx, &Gy);
        grid[Gy * WIDTH + bmp_x] = COLOR_GREEN;
        //printf("%d  %f\n", bmp_x, sin(x));
    }

    
    for(int bmp_x = 500; bmp_x < 1000; bmp_x++){  //TODO: Graphen abhängig von k machen
        toMath(bmp_x, 0, &x, &y);
        float a = (float)x/10;
        float b = u(x,1);
        toBMP(x, b, &Gx, &Gy);
        printf("%f   %f  %f   %f\n", x, u(x,10),  a, sin(x));
        grid[Gy * WIDTH + bmp_x] = COLOR_BLUE;
    }

    bmp_create("ex1.bmp", grid, WIDTH, HEIGHT);
    free(grid);
    return 0;
}

