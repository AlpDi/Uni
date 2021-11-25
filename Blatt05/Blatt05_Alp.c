#include <stdio.h> 
#include <time.h>
#include <stdlib.h>

#define NR_TYPES  8
#define NR_COLOURS  4
#define NR_CARDS  NR_TYPES * NR_COLOURS
#define NR_PLAYERS  4
#define CARDS_HAND  4

#define NONE   -1

#define SEVEN  0 // Sieben
#define EIGHT  1 // Acht
#define NINE   2 // Neun
#define TEN    3 // Zehn
#define JACK   4 // Bube, Bauer
#define QUEEN  5 // Königin
#define KING   6 // König
#define ACE    7 // Ass

#define HEARTS    0 // Herz
#define DIAMONDS  1 // Karo
#define CLUBS     2 // Kreuz
#define SPADES    3 // Pik

void print_card(int card) {
    int colour = card / NR_TYPES;
    int type = card % NR_TYPES;

    if(card == NONE) {
        printf("--- END --- "); // end of deck or gamer cards
        return;
    }
    /* print colour */
    if (colour == HEARTS)
        printf("HERZ ");
    else if (colour == DIAMONDS)
        printf("KARO ");
    else if (colour == CLUBS)
        printf("KREUZ ");
    else
        printf("PIK ");

    /* print type of card */
    if (type >= SEVEN && type <= TEN)
        printf("%d", 7 + type - SEVEN);
    else if (type == JACK)
        printf("BUBE");
    else if (type == QUEEN)
        printf("DAME");
    else if (type == KING)
        printf("KOENIG");
    else
        printf("ASS");
}


int main(void){
    int cards[NR_CARDS + 1 + NR_PLAYERS];
    int i, j, k;
    int pc;
    int ablage;

    if (NR_CARDS <= NR_PLAYERS * (CARDS_HAND + 1)) {
        printf("\n\n%d Karten sind nicht genug fuer %d Spieler je %d Karten", NR_CARDS, NR_PLAYERS, CARDS_HAND);
        exit(0);
    }

    for (i = 0; i < NR_CARDS; i++)
        cards[i] = i;  /* every element contains its own position */
    /** initialize first card on deck and first cards of players **/
    for (i = 0; i <= NR_PLAYERS; i++)
        cards[NR_CARDS + i] = NONE;

    // shuffle
    srand(time(NULL));  /* start random number generator */
    for (i = NR_CARDS; i; i--) {
        j = rand() % i ;  /* random variable modulo remaining cards */
        /* swap entries of fields i and j */
        k = cards[i];
        cards[i] = cards[j];
        cards[j] = k;
    }


    //ask if player wants to start the game
    printf("[0] - Spiel Starten  [1] - Beenden");
    fflush( stdout );
    scanf("%d", &k);
    if (k != 0 && k != 1)
            printf("Fehlerhafte Eingabe!");
    else if (k == 1)
        exit(0);
    else{
        printf("Spiel beginnt\n");
        /** distribute cards to every gamer **/
        for (i = 1; i <= NR_PLAYERS; i++) {
            /* first card on deck to gamer i */
            pc = cards[NR_CARDS];
            cards[NR_CARDS + i] = pc;
            /* loop through cards for the hand of gamer i */
            for (j = 1; j < CARDS_HAND; j++)
                pc = cards[pc];
            /* update first card on deck */
            cards[NR_CARDS] = cards[pc];
            /* last card of gamer i is identified by a NONE-entry */
            cards[pc] = NONE;
        }

    

    for(int i = 0; cards[NR_CARDS + 1] != NONE; i++){
        
        if(i==0){
            printf("Es liegt:\n");
            print_card(cards[NR_CARDS]);
            pc = cards[NR_CARDS];
            cards[NR_CARDS] = NONE;
            cards[NR_CARDS] = cards[pc];
            
            printf("\n");
        }
        //print cards for player 1 
        printf("Deine Karten sind:\n");
        pc = cards[NR_CARDS + 1]; // first card
        while(pc!=NONE){
            print_card(pc);
            if(cards[pc]!=NONE)
              printf(", ");
            pc = cards[pc];
        }
        printf("\n");
        printf("[1 - %d] - Karte legen, [0] - aufnehmen, [-1] - Spiel beenden\n", 4);
        scanf("%d", &k);
        if(k==-1)
            exit(0);
        else if(k==0){
            int ex = 0;
            int temp = cards[NR_CARDS];
            pc = cards[NR_CARDS];
            cards[NR_CARDS] = cards[pc];
            pc = cards[NR_CARDS + 1];
            while(ex != NONE){
                if(cards[pc] == NONE){
                    cards[pc] = temp;
                    printf("\n");print_card(pc);printf("\n");
                    cards[temp] = NONE;
                    ex = NONE;
                }
                pc = cards[pc];
                
            }
        }
        //karte ablegen
        else{
            int temp;
            pc = cards[NR_CARDS + 1];
            for(i = 1; i < k; i++){
                temp = pc;
                pc = cards[pc];
                
            }
            ablage = pc;
            cards[temp] = cards[pc];
            pc = cards[pc];
            printf("Es liegt: ");
            print_card(ablage);
            printf("\n");
        }

        //gegenspieler 
        for(i = 2; i <= 4; i++){
            int temp;
            pc = NR_CARDS + i;
            while(pc!=NONE){
                temp = pc;
                if(cards[pc] / NR_TYPES == ablage / NR_TYPES || cards[pc] % NR_TYPES == ablage % NR_TYPES )
                    ablage = pc;
                pc = cards[pc];
                }
                cards[temp] = cards[pc];
                pc = cards[pc];
                
            }
        printf("Es liegt: ");
        print_card(ablage);
        printf("\n");
    }

    
    }
    return 0;
}