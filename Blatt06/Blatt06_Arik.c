#include "libBMP.h"
#include <stdio.h>
#include <math.h>

// x being width, BMP size !!! NEEDS TO BE FLOAT !!!
#define WIDTH 4000.0
#define HEIGTH 1000.0

// axis positions
#define GRID_X_0 0.1 * HEIGTH
#define GRID_Y_0 0.5 * WIDTH

#define MIN_X -2
#define MAX_X 4
#define MIN_Y -1.2
#define MAX_Y 1.2

// smaller stpewidth means finer curves
#define STEPWIDTH 0.001

/*
int create_blank(void) {
  int x,y;
  uint32_t* arr;
  arr = (uint32_t*) malloc (WIDTH * HEIGTH * sizeof(uint32_t));

  for (x = 0; x < WIDTH; x++) {
    for (y = 0; y < HEIGTH; y++) {
      arr[y * WIDTH + x] = COLOR_WHITE;
    }
  }
  bmp_create("plot.bmp", arr, WIDTH, HEIGTH);
  free(arr);
  return 0;
}
*/

void toBMP(double matX, double matY, int *bmpX, int *bmpY) {
  *bmpX = (matX - MIN_X) * WIDTH / (MAX_X - MIN_X);
  *bmpY = HEIGTH - (matY - MIN_Y) * HEIGTH / (MAX_Y - MIN_Y);
}

void toMAT(int bmpX, int bmpY, double *matX, double *matY) {
  *matX = MIN_X + bmpX * (MAX_X - MIN_X) / WIDTH;
  *matY = MIN_Y + (HEIGTH - bmpY) * (MAX_Y - MIN_Y) / HEIGTH;
}

void test_toBMP(void) {
  double orig_x, orig_y;
  int bmp_x, bmp_y;
  for (orig_x = -20.0; orig_x <= 40.0; orig_x += 10.0) {
    for (orig_y = -20.0; orig_y <= 40.0; orig_y += 10.0) {
      toBMP(orig_x, orig_y, &bmp_x, &bmp_y);
      printf("X: %.0f\tY: %.0f\tBMP X: %d\tBMP Y: %d\n", orig_x, orig_y, bmp_x, bmp_y);
    }
  }
}

int in_function(double x, double y, double y_max) {
  double test_y;

  test_y = sin(x);

  if (test_y <= y && test_y > y_max) {
    // printf("returned 1 for sin(%f) ? %f => %f to %f\n", x, test_y, y, y_max);  // ugly debugging
    return 1;
  } else {
    return 0;
  }
}

int main (void) {
  double x, y, ym;
  int BMP_x, BMP_y, x0, y0;
  uint32_t* arr;
  arr = (uint32_t*) malloc(WIDTH * HEIGTH * sizeof(uint32_t));
  toBMP(0.0, 0.0, &x0, &y0);
  for (BMP_x = 0; BMP_x < WIDTH; BMP_x++) {
    for (BMP_y = 0; BMP_y < HEIGTH; BMP_y++) {
      toMAT(BMP_x, BMP_y, &x, &y);
      toMAT(BMP_x, BMP_y+1, &x, &ym);
      if (in_function(x, y, ym)) {
        arr[(int) (BMP_y * WIDTH + BMP_x)] = COLOR_BLUE;
      } else if (BMP_x == x0 || BMP_y == y0) {
        arr[(int) (BMP_y * WIDTH + BMP_x)] = COLOR_BLACK;
      } else {
        arr[(int) (BMP_y * WIDTH + BMP_x)] = COLOR_WHITE;
      }

    }
  }
  bmp_create("plot.bmp", arr, WIDTH, HEIGTH);
  free(arr);
  return 0;
}
