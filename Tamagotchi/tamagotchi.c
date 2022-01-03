#include "tamagotchi.h"
#include <stdio.h>
#include <stdlib.h>

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

void print_pet(tamagotchi pet){
    printf("name: %s\n", pet.name);
    printf("food status: %d\n", pet.food_status);
    printf("hapy status: %d\n", pet.happy_status);
    printf("discipline: %d\n", pet.discipline);
    printf("stage: %d\n", pet.stage);
    printf("hygiene: %d\n", pet.hygiene);
    printf("health: %d\n", pet.health);
}


void load(FILE savefile, tamagotchi *pet){
    // open file
    pet->discipline = ?;
    pet->food_status = ?;
    pet->happy_status = ?;
    pet->health = ?;
    pet->hygiene = ?;
    pet->name = ?;
    pet->stage = ?;
}

void save(tamagotchi pet, FILE savefile){
    // save to file
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
    pet->discipline -= intensity;
    // reduce fun when scolding? or remove completely?
}

void heal(tamagotchi *pet, int strength){
    if (pet->hygiene < 1){
        pet->hygiene += strength;
    }
    if (pet->health < 1){
        pet->hygiene += strength;
    }
}

void update_status(tamagotchi *pet, int millis){
    int actions = ?;  // randomize based on passed time, stronger effect over time
    pet->food_status -= actions;  // tendency: faster decaying
    pet->happy_status -= actions;  // tendency: decay based on health, hygiene and food status
    pet->health -= actions;  // tendency: decay slowed down by good hygiene
    pet->hygiene -= actions;
    pet->stage += actions;  // tendency: decay much slower
    // all of this needs more exact approximations
}
