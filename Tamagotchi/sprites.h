typedef struct Sprites{
    char* egg;
    char* baby;
    char* teen;
    char* adult;
    char* dead;
} Sprites;

Sprites sprites_init(void);
void print_sprites(Sprites sprites);
