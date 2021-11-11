#include <stdio.h>
#include <stdint.h>

int main() {
  int16_t y = 1024, z = 65; 

  y = y * z;
  printf("1. Ausgabe: %d\n", y);  //1024*65 = 66560, range von int16_t ist -32768 bis +32,767 -> 66560 - 65536 = 1024
  printf("2. Ausgabe: %d\n", y / 3 * 3 - 3 * y / 3); //da y von typ int ist, wird y / 3 von 341.333 gerundet auf 341 -> 341 - 342 = -1
  printf("\n");

  return 0;
}
