#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libBMP.h"

// maximal recusrion depth
#define N_MAX 255

// x being width, BMP size !!! NEEDS TO BE FLOAT !!!
#define WIDTH 6000.0
#define HEIGTH 4000.0

// size of content
#define MIN_X -2
#define MAX_X 1
#define MIN_Y -1
#define MAX_Y 1

// smaller stpewidth means finer curves
#define STEPWIDTH 0.001

/*
Start: c with depth 0, z = 0

Recursion: z_(+1) = z ^ 2 + c

Break: |z| >= 2 or depth > N_MAX

If |z| >= 2 then return depth

Else return EXISTS
*/

int mandelbrot_depth(double c_real, double c_imaginary, double last_real, double last_imaginary, int depth) {
  if (depth >= N_MAX) {
    //printf("Finished for %f %fi, including.\n", c_real, c_imaginary);
    return -1;
  }

  double z_real, z_imaginary;
  z_real = last_real * last_real - last_imaginary * last_imaginary + c_real;
  z_imaginary = 2 * last_real * last_imaginary + c_imaginary;

  if (sqrt(z_real * z_real + z_imaginary * z_imaginary) >= 2) {
    //printf("Finished for %f %fi, excluding.\n", c_real, c_imaginary);
    return depth;
  }
  return mandelbrot_depth(c_real, c_imaginary, z_real, z_imaginary, depth + 1);
}

void toBMP(double matX, double matY, int *bmpX, int *bmpY) {
  *bmpX = (matX - MIN_X) * WIDTH / (MAX_X - MIN_X);
  *bmpY = HEIGTH - (matY - MIN_Y) * HEIGTH / (MAX_Y - MIN_Y);
}

void toMAT(int bmpX, int bmpY, double *matX, double *matY) {
  *matX = MIN_X + bmpX * (MAX_X - MIN_X) / WIDTH;
  *matY = MIN_Y + (HEIGTH - bmpY) * (MAX_Y - MIN_Y) / HEIGTH;
}

int mandelbrot_color(double x, double y) {
  int depth = mandelbrot_depth(x, y, 0, 0, 0);
  if (depth < 0) {
    return COLOR_BLACK;
  } else if (depth > 24) {
    return COLOR_RED;
  } else if (depth > 8) {
    return COLOR_BLUE;
  } else if (depth > 3) {
    return COLOR_GREEN;
  } else {
    return COLOR_WHITE;
  }
}

int main (void) {
  double x, y;
  int BMP_x, BMP_y, x0, y0;
  uint32_t* arr;
  arr = (uint32_t*) malloc(WIDTH * HEIGTH * sizeof(uint32_t));
  toBMP(0.0, 0.0, &x0, &y0);
  for (BMP_x = 0; BMP_x < WIDTH; BMP_x++) {
    for (BMP_y = 0; BMP_y < HEIGTH; BMP_y++) {
      toMAT(BMP_x, BMP_y, &x, &y);
      arr[(int) (BMP_y * WIDTH + BMP_x)] = mandelbrot_color(x, y);
    }
  }
  bmp_create("mandelbrot.bmp", arr, WIDTH, HEIGTH);
  free(arr);
  return 0;
}
