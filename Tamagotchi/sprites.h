typedef char* Sprite;

typedef struct Sprites{
    Sprite egg;
    Sprite baby;
    Sprite teen;
    Sprite adult;
    Sprite dead;
} Sprites;

Sprites sprites_init();
void print_sprite(Sprite sprite);
void print_sprites(Sprites sprites);
