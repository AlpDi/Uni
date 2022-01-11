#include "tamagotchi.h"
#include "sprites.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




#include <stdio.h>

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
    #endif
#elif defined(__hpux)
    #define PLATFORM_NAME "hp-ux" // HP-UX
#elif defined(_AIX)
    #define PLATFORM_NAME "aix" // IBM AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
#else
    #define PLATFORM_NAME NULL
#endif

// Return a name of platform, if determined, otherwise - an empty string
const char *get_platform_name() {
    return (PLATFORM_NAME == NULL) ? "None/Unknown" : PLATFORM_NAME;
}

void clear_terminal(){
    if (strcmp(PLATFORM_NAME, "windows") == 0){ system("cls"); }
    else if (strcmp(PLATFORM_NAME, "linux") == 0){ system("clear"); }
    else { printf("System %s was not expected.\nCant clear screen!\n\n", PLATFORM_NAME); }
}

int main(void){
    int chocolate_bar = 2;

    printf("Running on system %s\n", get_platform_name());

    tamagotchi terry = pet_init("terry");
    
    feed(&terry, chocolate_bar);
    //print_pet(terry);
    Sprites sprites = sprites_init();
    //print_sprites(sprites);

    char input_menu = 0;
    while (input_menu != 'n' && input_menu != 'l' && input_menu != 'q') {
        printf("N: New game\nL: Load save file\nQ: Quit\n");
        scanf(" %c", &input_menu);
        input_menu = input_menu | 32;
        switch (input_menu) {
            case 'n':
                terry = pet_init("terry");
                clear_terminal();
                break;
            case 'l':
                printf("Loading from save file...\n");
                terry = pet_init("");
                load("save", &terry);
                break;
            case 'q':
                return 0;
            default:
                printf("Unknown command for %c!\n", input_menu);
                break;
        }
    }

    int loop = 1;

    while (loop){
        clear_terminal();
        char* act_sprite = "No Sprite loaded yet";
        char user_response;

        switch (terry.stage) {
            case 0:
                act_sprite = sprites.egg;
                break;
            case 1:
                act_sprite = sprites.baby;
                break;
            case 2:
                act_sprite = sprites.teen;
                break;
            case 3:
                act_sprite = sprites.adult;
                break;
            case 4:
                act_sprite = sprites.dead;
                break;
            default:
                break;
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
        scanf(" %c", &user_response);
        user_response = user_response | 32;
        switch(user_response){
            case 'a':
                feed(&terry, chocolate_bar);
                // TODO food menu
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
                clear_terminal();
                char input = 0;
                while (input != 'y' && input != 'n'){
                    printf("\n Do you want to save? [Y/N] \n");
                    scanf(" %c", &input);
                    input = input | 32;
                }
                if(input == 'y') {
                    save(terry, "save");
                    clear_terminal();
                    return 0;
                } else {
                    clear_terminal();
                    return 0;
                }
            default:
                printf("Unknown command for %c!\n", input_menu);
                break;
        }
    }
}
