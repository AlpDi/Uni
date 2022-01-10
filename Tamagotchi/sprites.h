typedef struct Sprites{
    char* egg;
    char* baby;
    char* teen;
    char* adult;
    char* dead;
} Sprites;

Sprites sprites_init();
Sprites print_sprites(Sprites sprites);
