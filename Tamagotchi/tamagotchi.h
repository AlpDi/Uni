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

void feed(tamagotchi *pet, int food);
void play(tamagotchi *pet, int fun);
void scold(tamagotchi *pet, int intensity);
void heal(tamagotchi *pet, int strength);

void print_pet(tamagotchi pet);

