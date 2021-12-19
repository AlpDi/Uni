#include "tamagotchi.h"
#include "sprites.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    tamagotchi terry = pet_init("terry");
    print_pet(terry);
    Sprites sprites = sprites_init();
    print_sprites(sprites);
}