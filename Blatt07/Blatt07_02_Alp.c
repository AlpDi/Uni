#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <gdiplus.h>
#include "libBMP.h"
#define W  6400
#define H  3200
#define xMin -2.0
#define xMax  1.0
#define yMin -1.0
#define yMax  1.0
#define nMax 500

void toMath(int bmp_x , int bmp_y, double* x, double* y) {
    
    *x = xMin + ((double) bmp_x * (xMax - xMin)) / W;
    *y = yMin + ((double)(H - bmp_y) * (yMax - yMin)) / H;
}

int mandelbrot(double r, double iy, double zr, double ziy, int n){
    if((n<=nMax)&&((zr*zr+ziy*ziy)<2)){
        double zr_new = (zr*zr-ziy*ziy+r);
        double ziy_new = (2*zr*ziy+iy);
        //punkt bleibt in menge -> schwarz
        if ((zr_new == zr) && (ziy_new == ziy)) {
            return nMax;
        }
        n = mandelbrot(r, iy, zr_new, ziy_new, n+1);
    }
    return n;
}

int color(double x, double y){
    int n = mandelbrot(x, y, 0.0, 0.0, 0);
    //farbe repräsentiert wie weit der punkt außerhalb der menge landet
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

    //Rekursionstiefe, lagt bei zu hoher auflösung und nmax code=3221225477
    //printf("%d\n", n); 
    return col;
}

int main (){
    uint32_t* A = (uint32_t*) malloc (W * H * sizeof(uint32_t));

    
    for(int i = 0;i < H; i++){
        for(int j = 0; j < W; j++){
            double x,y;
            toMath(j,i,&x,&y);
            A[i*W+j] = color(x,y);
        }
    }
    bmp_create("mandelbrot.bmp", A, W, H);


    free(A);
    return 0;
}