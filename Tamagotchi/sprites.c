#include "sprites.h"
#include "tamagotchi.h"
// #include <stdio.h>

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
     (   __   /''` ___\n\
     //\\\\ //\\\\    /___\\ \0";


     sprites.teen = "\
                   .-.\n\
     (____________()6 `-,\n\
     (   _______   /''` ___\n\
     //\\\\      //\\\\    /___\\ \0";

     sprites.adult = "\
                                  .-.\n\
     (___________________________()6 `-,\n\
     (   ______________________   /''`  ___\n\
     //\\\\                      //\\\\    /___\\ \0";


     sprites.dead = "\
             _.---,._,'\n\
       /' _.--.<\n\
         /'     `'\n\
       /' _.---._____\n\
       \\.'   ___, .-'`\n\
           /'    \\\\             .\n\
         /'       `-.          -|-\n\
        |                       |\n\
        |                   .-'~~~`-.\n\
        |                 .'         `.\n\
        |                 |  R  I  P  |\n\
        |                 |           |\n\
        |                 |           |\n\
         \\              \\\\|           |//\n\
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\0";


    return sprites;
}

Sprites print_sprites(Sprites sprites){
    printf("%s\n\n%s\n\n%s\n\n%s\n\n%s\n\n", sprites.egg, sprites.baby,sprites.teen, sprites.adult, sprites.dead);
    return sprites;
}
