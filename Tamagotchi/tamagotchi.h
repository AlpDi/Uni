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
void feed(tamagotchi pet, int food);
void play(tamagotchi happy_status);
void scold(tamagotchi discipline_status);
tamagotchi print_pet(tamagotchi pet);