#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include "libBMP.h"
#define W  1600
#define H  800
#define xMin -2.0
#define xMax  1.0
#define yMin -1.0
#define yMax  1.0

void toMath(int bmp_x , int bmp_y, double* x, double* y) {
    if ((bmp_x < 0) || (bmp_x > W) || (bmp_y < 0) || (bmp_y > H)) {
        *x = xMin;
        *y = yMin;
        return;
    }
    *x = xMin + ((double) bmp_x * (xMax - xMin)) / W;
    *y = yMin + ((double)(H - bmp_y) * (yMax - yMin)) / H;
}

int mandelbrot(double x, double y, double zx, double zy, int n, int nMax){
    if((n<=nMax)&&((zx*zx+zy*zy)<2)){
        double zx_new = (zx*zx-zy*zy+x);
        double zy_new = (2*zx*zy+y);
        if ((zx_new == zx) && (zy_new == zy)) {
            return nMax;
        }
        n = mandelbrot(x, y, zx_new, zy_new, n+1, nMax);
    }
    return n;
}

int main (){
    uint32_t* A = (uint32_t*) malloc (W * H * sizeof(uint32_t));

    int n;
    int nMax = 100;
    
    for(int i = 0;i < H; i++){
        for(int j = 0; j < W; j++){
            double x,y;
            toMath(j,i,&x,&y);
            n = mandelbrot(x, y, 0.0, 0.0, 0, nMax);
            printf("%d\n", n);
            uint32_t col = COLOR_BLACK;
            if (n < 5){ 
                col = COLOR_WHITE;
            } 
                else if (n < 10) {
                    col = COLOR_RED;
                }
                else if (n < 20) {
                    col = COLOR_GREEN;
                }
                else if(n< nMax) {
                    col = COLOR_BLUE;
                }
            A[i*W+j] = col;
        }
    }
    bmp_create("mandelbrot.bmp", A, W, H);


    free(A);
    return 0;
}