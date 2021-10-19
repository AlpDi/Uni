#include <stdio.h>
#include <stdint.h>

int main() {
  int16_t y = 1024, z = 65; // auch "short" als Datentyp verwendbar

  y = y * z;
  printf("1. Ausgabe: %d\n", y);
  printf("2. Ausgabe: %d\n", y / 3 * 3 - 3 * y / 3);
  printf("\n");

  return 0;
}
