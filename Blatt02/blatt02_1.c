
#include <stdio.h>
#include <stdint.h>

int main() {
  int16_t a_16, b_16, c_16;     //int16 hat range von -32768 .. 32767
  int32_t a_32, b_32, c_32;     //int32 hat range von -2,147,483,648 .. 2,147,483,647
  uint16_t a_u16, b_u16, c_u16; //uint16 hat range von 0 .. 65,535 

  b_16 = a_16 = 22222;
  b_32 = a_32 = 22222;

  c_32 = a_32 + b_32;   //44444 in range von int32
  c_16 = a_16 + b_16;   //44444 nicht mehr in range von int16 -> wrap around
  printf("a_32 + b_32 = %d + %d = %d \n\n", a_32, b_32, c_32);
  printf("a_16 + b_16 = %hd + %hd = %hd\n\n", a_16, b_16, c_16);

  a_u16 = a_16 + c_32; //66666 nicht in range von uint16 -> wraparound
  printf("a_16 + c_32 = %hd + %d = %hu\n\n", a_16, c_32, a_u16);

  a_u16 = 2222;
  b_u16 = -222; //wraparound da unsigned -> 65314
  c_u16 = a_u16 + b_u16;
  printf("a_u16 + b_u16 = %hu(=%hd) +%hu(=%hd) = %hu(=%hd)\n\n", a_u16,
         a_u16, b_u16, b_u16, c_u16, c_u16);

  a_32 = 555;
  b_32 = 1001;
  c_16 = c_32 = a_32 * b_32; //wraparound bei c_16
  printf("c_16 = c_32 = a_32 * b_32\n");
  printf("%hd = %d = %d * %d\n\n", c_16, c_32, a_32, b_32);
  c_32 = c_16 = a_32 * b_32; //wraparound bei c_16
  printf("c_32 = c_16 = a_32 * b_32\n");
  printf("%d = %hd = %d * %d\n\n", c_32, c_16, a_32, b_32);

  return 0;
}
