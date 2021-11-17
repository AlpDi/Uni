/*****************************************************************************
* mischen_beispielc                                                          *
*                                                                            *
*   Prozedurale Programmierung WS 2021/2022                                  *
*                                                                            *
*   kleines Beispielprogramm fuer den Knuth-Fisher-Yates Algorithmus         *
*                                                                            *
*   Parameter: keine                                                         *
*   Rueckgabe: 0                                                             *
*                                                                            *
* Autor: M. Lange, Florian Buenger                                           *
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
#define QUEEN  5 // Königin
#define KING   6 // König
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
 * call main function without input parameter
**/
int main(void) {

  /* array containing all cards */
  int cards[NR_CARDS];
  /* loop variables */
  int i, j, k;

  /* check if deck is big enough for the number of players */
  if (NR_CARDS <= NR_PLAYERS * (CARDS_HAND + 1)) {
    printf("\n\n%d Karten sind nicht genug fuer %d Spieler je %d Karten", NR_CARDS, NR_PLAYERS, CARDS_HAND);
    exit(0);
  }

  /** initialize deck **/
  for (i = 0; i < NR_CARDS; i++)
    cards[i] = i;  /* every element contains its own position */

  /** print all cards of deck **/
  printf("\nDie Karten des Decks vor dem Mischen:\n");
  for (i = 0; i < NR_CARDS; i++) {
    printf("(%d) ", i);
    print_card(cards[i]);
    printf(",  ");
  }

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
  for (i = NR_CARDS - 1; i; i--) {
    j = rand() % (i + 1);  /* random variable modulo remaining cards */
    /* swap entries of fields i and j */
    k = cards[i];
    cards[i] = cards[j];
    cards[j] = k;
  }

  /** print all cards after permutation **/
  printf("\nDie Karten des Decks nach dem Mischen:\n\n");
  for (i = 0; i < NR_CARDS; i++) {
    printf("(%d) ", i);
    print_card(cards[i]);
    printf(",  ");
  }

  /* return without errors */
  return 0;
}

