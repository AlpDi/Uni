#include "tamagotchi.h"
#include "sprites.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    int chocolate_bar = 2;

    tamagotchi terry = pet_init("terry");
    feed(terry, chocolate_bar);
    print_pet(terry);
    Sprites sprites = sprites_init();
    print_sprites(sprites);
}