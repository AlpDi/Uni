#include "tamagotchi.h"
#include <stdio.h>
#include <unistd.h>


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

void load(char *savefile, tamagotchi *pet){
    // open file
    pet->discipline = 0;
    pet->food_status = 0;
    pet->happy_status = 0;
    pet->health = 0;
    pet->hygiene = 0;
    pet->name = 0;
    pet->stage = 0;
    // TODO read from file instead of setting to 0
}

void save(tamagotchi pet, char *savefile) {
    char filename[256] = "";
    sprintf(filename, "%s.tamagotchi", savefile);
    printf("\nContent:\n%s\n", filename);

    if (file_exists(filename)) {
        char user_response[255] = "";
        printf("File %s exists! Overwrite saved game? [y/N]");
        scanf("%s", &user_response);
        printf("\n");
        if (user_response[0] == 'y' || user_response[0] == 'Y') {
            printf("\nOverwriting %s ...\n", filename);
        } else {
            printf("\nSave game was aborted. No save was created.\n");
            return;
        }
    } else {
        printf("\nWriting %s ...\n", filename);
    }
    FILE *file;
    file = fopen(filename, "w");

    char save_data[512];
    sprintf(save_data, "[NAME]\n%s\n[FOOD_STATUS]\n%d\n[HAPPY_STATUS]\n%d\n[DISCIPLINE]\n%d\n[STAGE]\n%d\n[HYGIENE]\n%d\n[HEALTH]\n%d\n", pet.name, pet.food_status, pet.happy_status, pet.discipline, pet.stage, pet.hygiene, pet.health);
    // printf("\nContent:\n%s\n", save_data);

    fputs(save_data, (FILE *) file);
    fclose((FILE *) file);
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