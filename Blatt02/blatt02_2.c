#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void main(){

    uint16_t n = 42;
    uint16_t a = 32768;
    for(int i = 0; i <= 15; i++){
        printf("%d", n >= a ? 1 : 0);
        n*=2;
    }
}