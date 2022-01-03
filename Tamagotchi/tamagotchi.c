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

void feed(tamagotchi *pet, int food){
    pet->food_status = pet->food_status + food;
}


void play(tamagotchi pet);
void scold(tamagotchi pet);
