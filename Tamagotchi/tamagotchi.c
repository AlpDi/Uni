#include "tamagotchi.h"
#include <stdio.h>
// #include <stdlib.h>


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
    pet->discipline = NULL;
    pet->food_status = NULL;
    pet->happy_status = NULL;
    pet->health = NULL;
    pet->hygiene = NULL;
    pet->name = NULL;
    pet->stage = NULL;
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
    pet->hygiene += strength;
    pet->hygiene += strength;
    if (pet->hygiene > 10){ pet->hygiene = 10; }
    if (pet->health > 10){ pet->health = 10; }
}

void update_status(tamagotchi *pet, int millis){
    int actions = NULL;  // randomize based on passed time, stronger effect over time
    pet->food_status -= actions;  // tendency: faster decaying
    pet->happy_status -= actions;  // tendency: decay based on health, hygiene and food status
    pet->health -= actions;  // tendency: decay slowed down by good hygiene
    pet->hygiene -= actions;
    pet->stage += actions;  // tendency: decay much slower
    // all of this needs more exact approximations
}
