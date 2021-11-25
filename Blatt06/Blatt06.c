#include "libBMP.h"
#include <stdio.h>

// width being the x coordinate
#define HEIGTH 10
#define WIDTH 20

#define MIN_X - 0.5 * WIDTH
#define MIN_Y 0

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

void toBMP(int matX, int matY, int *bmpX, int *bmpY) {
  *bmpX = MIN_X + matX * (WIDTH - MIN_X) / WIDTH;
  *bmpY = - (MIN_Y + matY * (HEIGTH - MIN_Y) / HEIGTH);
}

void test_toBMP(void) {
  int mx, my, bmpx, bmpy;
  for (mx = 0; mx < 20; mx+=5) {
    for (my = 0; my < 20; my+=5) {
      toBMP(mx, my, &bmpx, &bmpy);
      printf("Math x: %d\tMath y: %d\tBMP x: %d\tBMP y: %d\n\n", mx, my, bmpx, bmpy);
    }
  }
}
