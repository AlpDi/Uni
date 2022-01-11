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

void print_pet(tamagotchi pet){
    printf("name: %s\n", pet.name);
    printf("food status: %d\n", pet.food_status);
    printf("happy status: %d\n", pet.happy_status);
    printf("discipline: %d\n", pet.discipline);
    printf("stage: %d\n", pet.stage);
    printf("hygiene: %d\n", pet.hygiene);
    printf("health: %d\n", pet.health);
    // print sprite somewhere here?
}

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

    int i = 0;
    char data_line[256];

    long int seconds_offline;

    while (fgets(data_line, 256, file)){
        printf("%s\n", data_line);
        if (strcmp(data_line, "[NAME]") != 0){
            pet->name = fgets(data_line, 256, file);
            printf("pet->name: %s\ndata_line: %s", pet->name, data_line);
        } else if (strcmp(data_line, "[FOOD_STATUS]") != 0){
            pet->food_status = strtol(fgets(data_line, 256, file), NULL, 10);
        } else if (strcmp(data_line, "[HAPPY_STATUS]") != 0){
            pet->happy_status = atoi(fgets(data_line, 256, file));
        } else if (strcmp(data_line, "[DISCIPLINE]") != 0){
            pet->discipline = atoi(fgets(data_line, 256, file));
        } else if (strcmp(data_line, "[STAGE]") != 0){
            pet->stage = atoi(fgets(data_line, 256, file));
        } else if (strcmp(data_line, "[HYGIENE]") != 0){
            pet->hygiene = atoi(fgets(data_line, 256, file));
        } else if (strcmp(data_line, "[HEALTH]") != 0){
            pet->health = atoi(fgets(data_line, 256, file));
        } else if (strcmp(data_line, "[SECONDS]") != 0){
            seconds_offline = strtol(fgets(data_line, 256, file), NULL, 10);
        }
        printf("%s\n", data_line);
        print_pet(*pet);
    }

    printf("You were away for %d seconds!\n", seconds_offline);

    return 0;
}

int save(tamagotchi pet, char *savefile) {
    char filename[256] = "";
    sprintf(filename, "%s.tamagotchi", savefile);

    if (file_exists(filename)) {
        char user_response;
        printf("File %s exists! Overwrite saved game? [y/N]");
        scanf("%s", &user_response);
        user_response = user_response | 32;
        if (user_response == 'y' || user_response == 'Y') {
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
    sprintf(save_data, "[NAME]\n%s\n[FOOD_STATUS]\n%d\n[HAPPY_STATUS]\n%d\n[DISCIPLINE]\n%d\n[STAGE]\n%d\n[HYGIENE]\n%d\n[HEALTH]\n%d\n[SECONDS]\n%ld\n", pet.name, pet.food_status, pet.happy_status, pet.discipline, pet.stage, pet.hygiene, pet.health, seconds);

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

void update_status(tamagotchi *pet, int millis){
    int actions = 0;  // randomize based on passed time, stronger effect over time
    // TODO implement proper value for strength/individualize for categories
    pet->food_status -= actions;  // tendency: faster decaying
    pet->happy_status -= actions;  // tendency: decay based on health, hygiene and food status
    pet->health -= actions;  // tendency: decay slowed down by good hygiene
    pet->hygiene -= actions;
    pet->stage += actions;  // tendency: decay much slower
    // all of this needs more exact approximations
}