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
    int *update_display;
    int *lock;
    int *game_active;
    time_t *last_update;
    tamagotchi *pet;
} pet_update;

tamagotchi pet_init(char* name);
void print_pet(tamagotchi pet, char *sprite, char *message);

int load(char *savefile, tamagotchi *pet);
int save(tamagotchi pet, char *savefile);


void feed(tamagotchi *pet, int food);
void play(tamagotchi *pet, int fun);
void scold(tamagotchi *pet, int intensity);
void heal(tamagotchi *pet, int strength);

void *update_looper(pet_update *old_pet);
