#define TIMELAPSE_FACTOR 1

#include "tamagotchi.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


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

void clear_screen(){
    if (strcmp(PLATFORM_NAME, "windows") == 0){ system("cls"); }
    else if (strcmp(PLATFORM_NAME, "linux") == 0){ system("clear"); }
    else { printf("System %s was not expected.\nCant clear screen!\n\n", PLATFORM_NAME); }
}

tamagotchi pet_init(char *name){
    tamagotchi pet;
    pet.name = name;
    pet.food_status = 0;
    pet.happy_status = 3;
    pet.stage = 0;
    pet.hygiene = 3;
    pet.health = 3;

    return pet;
}

int file_exists(char *filename){
    FILE *file = fopen(filename, "r");
    int exists = 0;
    if (file != NULL){
        exists = 1;
        fclose(file);
    }
    return exists;
}

int begins_with(char *long_string, char *short_searchstring){
    int i = 0;
    while (short_searchstring[i] && long_string[i] == short_searchstring[i]){ i++; }
    return (short_searchstring[i]) ? 0 : 1;
}

void print_pet(tamagotchi pet, char *sprite, char *message, char *dead_sprite){
    /*
    printf("name: %s\n", pet.name);
    printf("food status: %d\n", pet.food_updated);
    printf("happy status: %d\n", pet.happy_updated);
    printf("discipline_updated: %d\n", pet.discipline_updated);
    printf("stage_updated: %d\n", pet.stage_updated);
    printf("hygiene_updated: %d\n", pet.hygiene_updated);
    printf("health_updated: %d\n", pet.health_updated);
     */

    printf("------------------------\n");
    if (message[0] != '\0') {
        printf("> %s\n------------------------\n", message);
    }
    printf("%s", sprite);
    printf("\n------------------------");
    printf("\nHealth:      \t");
    for (int i = 0; i < pet.health; i++) {
        printf("🧡");
    } printf("\nFood:      \t");
    for (int i = 0; i < pet.food_status; i++) {
        printf("🍔");
    } printf("\nHappy:     \t");
    for (int i = 0; i < pet.happy_status; i++) {
        printf("😄");
    } printf("\nHygiene:   \t");
    for (int i = 0; i < pet.hygiene; i++) {
        printf("🧼");
    } 
    printf("\nName:      \t%s\n------------------------\n", pet.name);

    printf("A: feed  S: play  D: clean  F: heal\n");
    if(pet.stage >= 4){
        clear_screen();
        printf("%s", dead_sprite);
        printf("\n\n GAME OVER \n\n");
        exit(0);
    }
}

char data_line[256] = "";

int load(char *savefile, tamagotchi *pet){
    char filename[256] = "";
    sprintf(filename, "%s.tamagotchi", savefile);
    FILE *file;
    file = fopen(filename, "r");
    printf("Opening file %s ...\n", filename);

    if (file == NULL){
        printf("There is no valid save with the name %s, loading was aborted.\n", savefile);
        return 1;
    }


    long long int savetime;


    while (fgets(data_line, 256, file)){
        if (begins_with(data_line, "[NAME]")){
            pet->name = &data_line[6];
        }
        if (begins_with(data_line, "[FOOD_STATUS]")){
            pet->food_status = atoi(data_line+13);
        }
        if (begins_with(data_line, "[HAPPY_STATUS]")){
            pet->happy_status = atoi(data_line+14);
        }
        if (begins_with(data_line, "[STAGE]")){
            pet->stage = atoi(data_line+7);
        }
        if (begins_with(data_line, "[HYGIENE]")){
            pet->hygiene = atoi(data_line+9);
        }
        if (begins_with(data_line, "[HEALTH]")){
            pet->health = atoi(data_line+8);
        }
        if (begins_with(data_line, "[SECONDS]")){
            savetime = strtol(data_line+9, NULL, 10);
        }
    }

    time_t loadtime = time(NULL);
    time_t time_offline = loadtime - savetime;
    printf("You were away for %lld seconds!\n", time_offline);
    // TODO simulate time away based on time_offline (millis)
    update_status(pet, time_offline);

    return 0;
}

int save(tamagotchi pet, char *savefile) {
    char filename[256] = "";
    sprintf(filename, "%s.tamagotchi", savefile);

    if (file_exists(filename)) {
        int user_response = 0;
        printf("File %s exists! ", filename);
        do {
            printf("Overwrite saved game? [y/N]\n");
            user_response = getchar() | 32; while (user_response != ('\n' | 32) && getchar() != '\n'){}
        } while (user_response != 'y' && user_response != 'n' && user_response != ('\n' | 32));
        if (user_response == 'y') {
            printf("\nOverwriting %s ...\n", filename);
        } else {
            printf("\nSave game was aborted. No save was created.\n");
            return 1;
        }
    } else {
        printf("\nWriting %s ...\n", filename);
    }
    FILE *file;
    file = fopen(filename, "w");


    char save_data[512];
    time_t seconds = time(NULL);
    sprintf(save_data, "[FOOD_STATUS]%d\n[HAPPY_STATUS]%d\n[STAGE]%d\n[HYGIENE]%d\n[HEALTH]%d\n[SECONDS]%lld\n[NAME]%s\n", pet.food_status, pet.happy_status, pet.stage, pet.hygiene, pet.health, seconds, pet.name);

    fputs(save_data, (FILE *) file);
    fclose((FILE *) file);
    return 0;
}


void feed(tamagotchi *pet, int food){
    pet->food_status += food;
}


void play(tamagotchi *pet){
    time_t t;

    srand((unsigned) time(&t));

    int height = 20, width = 10;
    int state; 
    int *score = (int*) malloc(sizeof (int));



    state = 0;
    *score = 0;
    int x = width / 2;
    int y = height / 2;

    int fx = 1 + rand() % 8;
    int fy = 1 + rand() % 18;


    while(!state){
        clear_screen();
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                if(i == 0
                || i == width - 1
                || j == height - 1
                || j == 0){
                    printf("H");
                }
                else {
                    if (i == x && j == y)
                        printf("0");
                    else if (i == fx
                            && j == fy)
                        printf("*");
                    else
                        printf(" ");
                }
            }
        printf("\n");
        }
        printf("%d\n", *score);


        switch(getchar()){
            case 'a':
            sleep(0.01);
            y--;
            break;
        case 's':
            sleep(0.01);
            x++;
            break;
        case 'd':
            sleep(0.01);
            y++;
            break;
        case 'w':
            sleep(0.01);
            x--;
            break;
        case 'q':
            sleep(0.01);
            state = 1;
            break;
            }

        if(x < 0
        || x > width
        || y > height){
            state = 1;
        }

        if(x == fx && y == fy){
            fx = 1 + rand() % 8;
            fy = 1 + rand() % 18;
            *score += 1;
        }

        }
    pet->happy_status += *score;
    free(score);

}

void clean(tamagotchi *pet, int intensity){
    pet->hygiene += intensity;
}

void heal(tamagotchi *pet, int strength){
    pet->health += strength;
}

updated_t update_status(tamagotchi *pet, time_t passed_millis){
    updated_t updates = {0, 0, 0, 0, 0, 0};
    passed_millis *= TIMELAPSE_FACTOR;
    for (int i = 0; i < passed_millis; i++) {
        if (pet->food_status > 0) {
            int random = rand() % 20;
            if (random < 3) {
                pet->food_status -= 1;
                updates.food_updated += 1;
                updates.any_updated += 1;
            }
        }
        if (pet->happy_status > 0) {
            int random = rand() % (5 + 2 * pet->food_status);
            if (random < 1) {
                pet->happy_status -= 1;
                updates.happy_updated += 1;
                updates.any_updated += 1;
            }
        }
        if (pet->health > 0) {
            int random = rand() % (10 + 5 * pet->hygiene);
            if (random < 1) {
                pet->health -= 1;
                updates.health_updated += 1;
                updates.any_updated += 1;
            }
        }
        if (pet->hygiene > 0) {
            int random = rand() % 70;
            if (random < 1) {
                pet->hygiene -= 1;
                updates.hygiene_updated += 1;
                updates.any_updated += 1;
            }
        }
        if (pet->stage < 6) {
            int random = rand() % (10 + 10 * pet->happy_status);
            if (random < 1) {
                pet->stage += 1;
                updates.stage_updated += 1;
                updates.any_updated += 1;
            }
        }

    }
    return updates;
}
