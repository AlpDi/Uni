#include "tamagotchi.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

tamagotchi pet_init(char *name){
    tamagotchi pet;
    pet.name = name;
    pet.food_status = 0;
    pet.happy_status = 3;
    pet.discipline = 0;
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

void print_pet(tamagotchi pet, char *sprite, char *message){
    /*
    printf("name: %s\n", pet.name);
    printf("food status: %d\n", pet.food_status);
    printf("happy status: %d\n", pet.happy_status);
    printf("discipline: %d\n", pet.discipline);
    printf("stage: %d\n", pet.stage);
    printf("hygiene: %d\n", pet.hygiene);
    printf("health: %d\n", pet.health);
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
    } printf("\nDiscipline:\t");
    for (int i = 0; i < pet.discipline; i++) {
        printf("d");
    } printf("\nName:      \t%s\n------------------------\n", pet.name);

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
        printf("Current line:\t%s\n", data_line);
        if (begins_with(data_line, "[NAME]")){
            pet->name = &data_line[6];
        }
        if (begins_with(data_line, "[FOOD_STATUS]")){
            pet->food_status = atoi(data_line+13);
        }
        if (begins_with(data_line, "[HAPPY_STATUS]")){
            pet->happy_status = atoi(data_line+14);
        }
        if (begins_with(data_line, "[DISCIPLINE]")){
            pet->discipline = atoi(data_line+12);
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
    sprintf(save_data, "[FOOD_STATUS]%d\n[HAPPY_STATUS]%d\n[DISCIPLINE]%d\n[STAGE]%d\n[HYGIENE]%d\n[HEALTH]%d\n[SECONDS]%lld\n[NAME]%s\n", pet.food_status, pet.happy_status, pet.discipline, pet.stage, pet.hygiene, pet.health, seconds, pet.name);

    fputs(save_data, (FILE *) file);
    fclose((FILE *) file);
    return 0;
}


void feed(tamagotchi *pet, int food){
    pet->food_status += food;
}


void play(tamagotchi *pet, int fun){
    //create tictactoe field 
    // or snake?
    // or pong?
}

void scold(tamagotchi *pet, int intensity){
    pet->discipline += intensity;
    // reduce fun when scolding? or remove completely?
}

void heal(tamagotchi *pet, int strength){
    pet->hygiene += strength;
    pet->health += strength;
    if (pet->hygiene > 10) {pet->hygiene = 10;}
    if (pet->health > 10) {pet->health = 10;}
}

int update_status(tamagotchi *pet, time_t passed_millis){
    int updates = 0;
    for (int i = 0; i < passed_millis; i++) {
        // printf("updating pet as after %lld millis!\n", passed_millis);
        int random = rand() % 6;
        switch (random) {
            case 0:
            case 1:
                pet->food_status -= 1;
                updates += 1;
                break;
            case 2:
                pet->happy_status -= 1;
                updates += 1;
                break;
            case 3:
                pet->health -= 1;
                updates += 1;
                break;
            case 4:
                pet->hygiene -= 1;
                updates += 1;
                break;
            case 5:
                pet->stage += 1;
                updates += 1;
                break;
            default:
                break;
        }
    }
    return updates;
}

void *update_looper(pet_update *old_pet){
    while (*old_pet->game_active){
        sleep(1);
        if (*old_pet->lock == 0) {
            *old_pet->lock += 1; if (*old_pet->lock > 1) {
                *old_pet->lock -= 1;
                continue;
            }
            time_t time_dif = (long long int) time(NULL) - (long long int) *old_pet->last_update;
            // printf("Old Millis: %lld\nNew Millis: %lld\nPassed Millis: %lld\n", *old_pet->last_update, time(NULL), time_dif);
            *old_pet->last_update = time(NULL);
            if(update_status(old_pet->pet, time_dif)){
                old_pet->update_display += 1;
            }

            *old_pet->lock -= 1;
        }
    }
    return NULL;
}
