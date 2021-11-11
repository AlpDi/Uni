#include <stdio.h>
#include <stdint.h>

int main(){
    uint16_t a = 81;
    uint16_t b = 90;
    uint16_t c = a;
    uint16_t d = b;

    int temp;

    while(b!=0){
        temp = a%b; // temp = a - (b * (int)(a/b))
        a = b;
        b = temp;
    }
    printf("Der ggT von %d und %d ist %d\n",c,d, a);
}

