/*****************************************************************************
* Beispiel_Hoersaal_Uebung.c                                                 *
*                                                                            *
*   Prozedurale Programmierung WS 2021/2022                                  *
*                                                                            *
*   kleines Beispielprogramm zu Blatt 5                                      *
*     - Mischen von Karten                                                   *
*     - Verteilen der Karten                                                 *
*     - Verknuepfung der einzelnen Kartenlisten                              *
*                                                                            *
*   Parameter: keine                                                         *
*   Rueckgabe: 0                                                             *
*                                                                            *
* Autor: Florian Buenger                                                     *
* E-Mail: florian.buenger@tuhh.de                                            *
*                                                                            *
* Datum: 14.10.2021                                                          *
*****************************************************************************/

/** libraries **/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/** definitions **/
/* number of card-types */
#define NR_TYPES  8
/* number of crad-colours */
#define NR_COLOURS  4
/* number of cards */
#define NR_CARDS  NR_TYPES * NR_COLOURS
/* number of players */
#define NR_PLAYERS  4
/* every gamer starts with this number of cards in his hand */
#define CARDS_HAND  4

/* define flags */
#define NONE   -1
#define FTAKE  -2
#define FPUT   -3
#define FTURN  -4

/* define types */
#define SEVEN  0 // Sieben
#define EIGHT  1 // Acht
#define NINE   2 // Neun
#define TEN    3 // Zehn
#define JACK   4 // Bube, Bauer
#define QUEEN  5 // KÃ¶nigin
#define KING   6 // KÃ¶nig
#define ACE    7 // Ass

/* define colours */
#define HEARTS    0 // Herz
#define DIAMONDS  1 // Karo
#define CLUBS     2 // Kreuz
#define SPADES    3 // Pik

/**
 * print a given card
**/
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

/**
 * print all cards and additional entries of given card array
**/
void print_array(int cards[]) {
    int i;

    printf("\nIndex\tInhalt\tBedeutung");
    printf("\n----------------------------\n");
    for (i = 0; i < NR_CARDS + 1 + NR_PLAYERS; i++) {
        printf("(%d)\t%d\t", i,cards[i]);
        print_card(cards[i]);
        printf("\n");
        if(i==NR_CARDS-1)
            printf("----------------------------\n");
    }
    return;
}

/**
 * call main function without input parameter
**/
int main(void) {

    /* array containing all cards + first card on deck + first cards of players */
    int cards[NR_CARDS + 1 + NR_PLAYERS];
    /* loop variables */
    int i, j, k;
    int pc;

    /* check if deck is big enough for the number of players */
    if (NR_CARDS <= NR_PLAYERS * (CARDS_HAND + 1)) {
        printf("\n\n%d Karten sind nicht genug fuer %d Spieler je %d Karten", NR_CARDS, NR_PLAYERS, CARDS_HAND);
        exit(0);
    }

    /** initialize deck **/
    for (i = 0; i < NR_CARDS; i++)
        cards[i] = i;  /* every element contains its own position */
    /** initialize first card on deck and first cards of players **/
    for (i = 0; i <= NR_PLAYERS; i++)
        cards[NR_CARDS + i] = NONE;  /* initialize with NONE = -1, meaning that each gamer has zero cards in the beginning */

    /** print all cards of deck **/
    printf("\nDie Karten des Decks vor dem Mischen:\n");
    print_array(cards);

    /** ask user to continue program **/
    k = -1;
    do {
        printf("\n\nSollen die Karten gemischt werden?\n[0] - Ja,  [1] - Nein    ");
        fflush( stdout );
        scanf("%d", &k);
        if (k != 0 && k != 1)
            printf("Fehlerhafte Eingabe!");
    } while (k != 0 && k != 1);
    /* quit program */
    if (k == 1)
        exit(0);

    /** shuffle cards - Knuth-Fisher-Yates shuffle **/
    srand(time(NULL));  /* start random number generator */
    for (i = NR_CARDS; i; i--) {
        j = rand() % i ;  /* random variable modulo remaining cards */
        /* swap entries of fields i and j */
        k = cards[i];
        cards[i] = cards[j];
        cards[j] = k;
    }

    /** print all cards after permutation (without cycles) **/
    printf("\nDie Karten des Decks nach dem Mischen:\n\n");
    print_array(cards);

    do {
        printf("\n\nSollen die Karten auf die Spieler verteilt  werden?\n[0] - Ja,  [1] - Nein    ");
        fflush( stdout );
        scanf("%d", &k);
        if (k != 0 && k != 1)
            printf("Fehlerhafte Eingabe!");
    } while (k != 0 && k != 1);
    /* quit program */
    if (k == 1)
        exit(0);

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

    /** print all cards after distribution to gamers **/
    printf("\nDie Karten des Decks nach dem Verteilen:\n\n");
    print_array(cards);

    do {
        printf("\n\nSollen die Karten der Spieler und das Deck einzeln ausgegeben werden?\n[0] - Ja,  [1] - Nein    ");
        fflush( stdout );
        scanf("%d", &k);
        if (k != 0 && k != 1)
            printf("Fehlerhafte Eingabe!");
    } while (k != 0 && k != 1);
    /* quit program */
    if (k == 1)
        exit(0);

     /** print deck and cards of gamers individiually **/
    for (i = 0; i <= NR_PLAYERS; i++){
        if(i==0)
            printf("\nDeck: ");
        else
            printf("Karten von Spieler %d: ",i);
        pc = cards[NR_CARDS + i]; // first card
        while(pc!=NONE){
            print_card(pc);
            if(pc[cards]!=NONE)
              printf(", ");
            pc = cards[pc];
        }
        printf("\n");

    }

    /* return without errors */
    return 0;
}
