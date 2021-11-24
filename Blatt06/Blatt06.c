#include "libBMP.h"

#define H 400  // heigth
#define W 500  // width

int main() {
  int X,Y;
  uint32_t* data;
  data = (uint32_t*) malloc (W * H * sizeof(uint32_t));

  for (X = 0; X < W; X++) {
    for (Y = 0; Y < H; Y++) {
      if((Y/10)%2)
        data[Y * W + X] = COLOR_RED;
      else
        data[Y * W + X] = COLOR_GREEN;
    }
  }
  bmp_create("plot.bmp", data, W, H);
  free(data);
  return 0;
}
