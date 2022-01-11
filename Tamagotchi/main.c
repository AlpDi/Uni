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

    printf("N: New game\nL: Load save file\nQ: Quit\n");
    char input_menu;
    scanf(" %c", &input_menu);
    switch(input_menu){
        case 'n':
            break;
        case 'l':
            load("save", &terry);
            break;
        case 'q':
            return 0;
    }


    int loop = 1;

    while (loop){
        system("clear");
        char* act_sprite = "No Sprite loaded yet";
        char user_response;
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
        //TODO case insensitive machen
        scanf(" %c", &user_response);
        switch(user_response){
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
                system("clear");
                printf("\n Do you want to save? [Y/N] \n");
                char input;
                scanf(" %c", &input);
                if(input == 'y'){
                    save(terry, "save");
                    system("clear");
                    return 0;
                }
                else{
                    system("clear");
                    return 0;
                }
        } 
    }
}
