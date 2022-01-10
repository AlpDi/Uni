#include "tamagotchi.h"
#include "sprites.h"
// #include <stdlib.h>
#include <stdio.h>

int main(void){
    int chocolate_bar = 2;

    tamagotchi terry = pet_init("terry");
    feed(&terry, chocolate_bar);
    //print_pet(terry);
    Sprites sprites = sprites_init();
    //print_sprites(sprites);

    int loop = 1;

    while (loop){
        char* act_sprite = "No Sprite loaded yet";
        char input;
        if(terry.stage == 0){
            act_sprite = sprites.baby;
        }
        printf("---------------\n");
        //TODO in Funktion auslagern
        for(int i=0; i < terry.health; i++){
            printf("🧡");
        };
        printf("  ");
        for(int i=0; i < terry.food_status; i++){
            printf("🍔");
        };

        printf("\n\n%s\n\n", act_sprite);
        printf("---------------\n");
        printf("A: feed  S: play  D: scold F: heal\n");
        scanf("%c", &input);
        switch(input){
            case 'a':
                feed(&terry, chocolate_bar);
                break;
            case 's':
                play(&terry, 3);
                break;
            case 'd':
                scold(&terry, 2);
                break;
            case 'f':
                heal(&terry, 1);
                break;
            case 'q': 
                return 0;
        }
    }
}
