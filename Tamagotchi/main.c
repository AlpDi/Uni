#include "tamagotchi.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    tamagotchi terry = pet_init("terry");
    print_pet(terry);
}