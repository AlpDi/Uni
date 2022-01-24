#include <stdio.h> 
// #include "sprites.h"
#include <time.h>

typedef struct tamagotchi{

    char *name;
    int food_status;
    int happy_status;
    int discipline;
    int stage; //baby, child, teenager, adult
    int hygiene;
    int health;

} tamagotchi; 

typedef struct {
    int food_updated;
    int happy_updated;
    int health_updated;
    int hygiene_updated;
    int stage_updated;
    int discipline_updated;
    int any_updated;
}updated_t;

tamagotchi pet_init(char* name);
void print_pet(tamagotchi pet, char *sprite, char *message);

int load(char *savefile, tamagotchi *pet);
int save(tamagotchi pet, char *savefile);


void feed(tamagotchi *pet, int food);
void play(tamagotchi *pet, int fun);
void scold(tamagotchi *pet, int intensity);
void heal(tamagotchi *pet, int strength);

updated_t update_status(tamagotchi *pet, time_t passed_millis);
