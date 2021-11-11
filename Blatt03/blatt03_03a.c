#include <stdio.h>
#include <stdint.h>

int main(){
    uint16_t a = 25;
    uint16_t b = 5;
    uint16_t c = a;
    uint16_t d = b;


    while(a!=0 && b!=0){
        if(a > b){
            a = a - b;
        }
        else {
            b = b - a;
        }
    }

    
    if (a <= 0) {
    printf("Der ggT ist von %d und %d ist %d\n",c,d, b);
    } 
    else {
    printf("Der ggT ist von %d und %d ist %d\n",c,d, a);
    }
    return 0;

}