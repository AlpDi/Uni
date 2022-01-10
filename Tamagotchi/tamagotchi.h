#include <stdio.h>


typedef struct tamagotchi{

    char *name;
    int food_status;
    int happy_status;
    int discipline;
    int stage; //baby, child, teenager, adult
    int hygiene;
    int health;

} tamagotchi; 

tamagotchi pet_init(char* name);
void print_pet(tamagotchi pet);//, Sprites sprites);

void load(FILE savefile, tamagotchi *pet);  // nicht lieber als return-value?
void save(tamagotchi pet, FILE savefile);


void feed(tamagotchi *pet, int food);
void play(tamagotchi *pet, int fun);
void scold(tamagotchi *pet, int intensity);
void heal(tamagotchi *pet, int strength);

void update_status(tamagotchi *pet, int millis);  // Zeit muss eingebunden werden!