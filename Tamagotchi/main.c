#include "tamagotchi.h"
#include "sprites.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include <pthread.h>


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

void clear_terminal(){ //*
    if (strcmp(PLATFORM_NAME, "windows") == 0){ system("cls"); }
    else if (strcmp(PLATFORM_NAME, "linux") == 0){ system("clear"); }
    else { printf("System %s was not expected.\nCant clear screen!\n\n", PLATFORM_NAME); }
} //*/}

int main(void){
    int chocolate_bar = 2;

    printf("Running on system %s\n", get_platform_name());

    tamagotchi terry;  // = pet_init("terry");
    
    //feed(&terry, chocolate_bar);
    //print_pet(terry);
    Sprites sprites = sprites_init();
    //print_sprites(sprites);

    int input_menu; int failure = -1;
    do {
        do {
            printf("N: New game\nL: Load save file\nQ: Quit\n");
            input_menu = getchar() | 32;
            while (input_menu != ('\n' | 32) && getchar() != '\n') {}
        } while (input_menu != 'n' && input_menu != 'l' && input_menu != 'q');
        switch (input_menu) {
            case 'n':
                // new tamagotchi
                printf("How do you want to name your tamagotchi?\n");
                char name_buffer[255];
                int j = 0;
                do {
                    name_buffer[j] = (char) getchar();
                    if (name_buffer[j] != '\n') {
                        if (j == 0) {
                            name_buffer[j] &= -33;
                        } else {
                            name_buffer[j] |= 32;
                        }
                    } else {
                        name_buffer[j] = '\0';
                        if (j == 0) {
                            failure = 1;
                        } else {
                            failure = 0;
                        }
                    }
                    j++;
                } while (failure < 0);


                if (!failure){
                    printf("Your Tamagotchi will be named \'%s\'.\nIs this your wish? [Y|n]\n", (char *) name_buffer);
                    int response;
                    do {
                        response = getchar() | 32;
                        while (response != ('\n' | 32) && getchar() != '\n'){}
                    } while (response != 'y' && response != 'n' && response != ('\n' | 32));
                    if (response == 'n') {
                        printf("Name was not accepted.\n");
                        failure = -1;
                        clear_terminal();
                        break;
                    }
                } else { printf("That name did\'nt work...\n"); break; }

                terry = pet_init((char *)name_buffer);
                clear_terminal();
                break;
            case 'l':
                // load tamagotchi
                printf("Loading from save file...\n");
                terry = pet_init("");
                failure = load("save", &terry);
                if (failure) {
                    printf("Failed to load.\n");
                }
                break;
            case 'q':
                return 0;
        }
    } while (failure);
    int loop = 1;

    char* message_status = "";

    int lock_vars = 0;
    pet_update old_pet;
    old_pet.pet = &terry;
    old_pet.game_active = &loop;
    int update_display = 0;
    old_pet.update_display = &update_display;
    time_t last_update = time(NULL);
    old_pet.last_update = &last_update;
    old_pet.lock = &lock_vars;

    srand(time(NULL));

    pthread_t thread_id_update_status;
    pthread_create(&thread_id_update_status, NULL, update_looper, (void *) &old_pet);

    while (loop){
        clear_terminal();
        char* act_sprite = "No Sprite loaded yet";
        int user_response;

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
        print_pet(terry, act_sprite, message_status);

        /*
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
        */

        do {
            printf("A: feed  S: play  D: scold F: heal\n");
            user_response = getchar(); while (update_display == 0 && user_response != '\n' && getchar() != '\n'){}
            user_response = user_response | 32;
        } while (update_display == 0 && user_response != 'a' && user_response != 's' && user_response != 'd' && user_response != 'f' && user_response != 'q');
        if (update_display){
            update_display = 0;
            continue;
        }
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
                int input;
                do {
                        printf("\n Do you want to save? [Y/n] \n");
                        input = getchar(); while (input != '\n' && getchar() != '\n'){}
                        input |= 32;
                }
                while (input != 'y' && input != 'n' && input != ('\n'|32));
                if(input != 'n') {
                    int failure = save(terry, "save");
                    if (!failure){
                        clear_terminal();
                        loop = 0;
                    } else {
                        message_status = "Failed to write.";
                    }
                } else {
                    clear_terminal();
                    loop = 0;
                }
                break;
        }
    }
    if (loop) {
        loop = 0;
        printf("\'loop\' was not 0 after game loop!");
    }
    pthread_join(thread_id_update_status, NULL);
}
