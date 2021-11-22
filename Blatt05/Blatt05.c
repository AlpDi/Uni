#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define START_CARDS 5

#define NR_VALUES 8
#define SEVEN  0
#define EIGHT  1
#define NINE   2
#define TEN    3
#define JACK   4
#define QUEEN  5
#define KING   6
#define ACE    7

#define NR_COLOURS 4
#define DIAMONDS 0
#define SPADES   1
#define HEARTS   2
#define CLUBS    3

//not-cards
#define NONE_CARD -1

void print_card(int card) {
  int value = card % NR_VALUES;
  int colour = card / NR_VALUES;

  if (card == NONE_CARD) {
    printf("__/ END \\__");
    return;
  }
  if (colour == DIAMONDS) {
    printf("Karo ");
  } else if (colour == SPADES) {
    printf("Pik ");
  } else if (colour == HEARTS) {
    printf("Herz ");
  } else {
    printf("Kreuz ");
  }

  if (value >= SEVEN && value < JACK) {
    printf("%d", value + 7);
  } else if (value == JACK) {
    printf("Bube");
  } else if (value == QUEEN) {
    printf("Dame");
  } else if (value == KING) {
    printf("Koenig");
  } else if (value == ACE) {
    printf("Ass");
  }
}

void print_card_array(int cards[]) {
  int i;
  printf("\nIndex\tInteger\tWertigkeit\n-------------------------------\n");
  for (i = 0; i < 37; i++) {
    printf("[%d]\t%d\t", i, cards[i]);
    print_card(cards[i]);
    printf("\n");
    if (i == 31)
      printf("-------------------------------\n");  // separator after card stack
  }
}

int main(void) {
  int cards[37];
  int i, j, k;  // just for c89-std compability...
  int player_cards;
  int player_active;
  int game_running;
  int last_layed;

  if (32 <= 4 * (START_CARDS + 1)) {
    printf("\n32 Karten sind nicht genug bei 4 Spielern mit %d Startkarten!", START_CARDS);
    exit(0);
  }

  for (i = 0; i < 32; i++) {
    cards[i] = i;
  }
  for (i = 32; i <= 36; i++) {
    cards[i] = NONE_CARD;
  }

  printf("\nKartendeck vor dem Mischen:\n");
  print_card_array(cards);

  /* Knuth-Fisher-Yates shuffle */
  srand(time(NULL));
  for (i = 32; i; i--) {
      j = rand() % i ;  /* random variable modulo remaining cards */
      /* swap entries of fields i and j */
      k = cards[i];
      cards[i] = cards[j];
      cards[j] = k;
  }

  printf("\nKartendeck nach dem Mischen:\n");
  print_card_array(cards);

  for (i = 1; i <= 4; i++) {
    player_cards = cards[32];
    cards[32 + i] = player_cards;

    for (j = 1; j < START_CARDS; j++) {
      player_cards = cards[player_cards];
    }
    cards[32] = cards[player_cards];
    cards[player_cards] = NONE_CARD;
  }

  printf("\nKartendeck nach dem Verteilen:\n");
  print_card_array(cards);

  for (i = 0; i <= 4; i++) {
    if (i == 0)
      printf("\nKartendeck: ");
    else
      printf("\nKarten von Spieler %d: ", i);
    player_cards = cards[32 + i];
    while (player_cards != NONE_CARD) {
      print_card(player_cards);
      if (player_cards[cards] != NONE_CARD)
        printf(", ");
      player_cards = cards[player_cards];
    }
    printf("\n");
  }

  game_running = 1; player_active = 1;

  while (game_running) {
    printf("\nAuf dem Ablagestapel liegt: ");
    print_card(last_layed); printf("\n");
    if (player_active == 1) {
      printf("Auf deiner Hand sind:\n\t");


      // print player cards
      i = 0;
      player_cards = cards[32 + player_active];
      while (player_cards != NONE_CARD) {
        printf("(%d) ", i);
        print_card(player_cards);
        if (player_cards[cards] != NONE_CARD)
          printf(", ");
        player_cards = cards[player_cards];
        i++;
      }
      printf("\n");
    }

    getchar();

    player_active = (player_active) % 4 + 1;
    printf("Naechster! (%d)\n", player_active);
  }

  return(0);
}
