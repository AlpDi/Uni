#include "tamagotchi.h"
#include "sprites.h"
#include <stdio.h>
#include <stdlib.h>

Sprites sprites_init(){
    Sprites sprites;
    sprites.egg = "\
     IIIII \n\
    IIIIIII\n\
    IIIIIII\n\
    IIIIIII\n\
     IIIII \0";


     sprites.baby = "\
              .-.\n\
     (_______()6 `-,\n\
     (   __   /''`\n\
     //\\\\ //\\\\ \0";

     sprites.adult = "\
                                  .-.\n\
     (___________________________()6 `-,\n\
     (   ______________________   /''`\n\
     //\\\\                      //\\\\ \0";


    return sprites;
}

Sprites print_sprites(Sprites sprites){
    printf("%s\n\n%s\n\n%s", sprites.egg, sprites.baby, sprites.adult);
}