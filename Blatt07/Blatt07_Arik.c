#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// with n element of {5, 6} being the length of the sides
#define N 5

int springerpfade = 0;

void print_board(int board[]) {
  int i;
  for (i = 0; i < (N * N); i++) {
    printf("%d", board[i]);
    if ((i + 1) % N == 0) {
      printf("\n");
    } else {
      printf("\t");
    }
  }
}

int board_done(int board[]) {
  int i;
  for (i = 0; i < N * N; i++) {
    if (board[i] == 0) {
      return 0;
    }
  }
  return 1;
}

int field_exists(int x, int y) {
  if (x < 0) {return 0;}
  if (y < 0) {return 0;}
  if (x >= N) {return 0;}
  if (y >= N) {return 0;}
  return 1;
}

void iterate_horse_move(int current_x, int current_y, int board[], int recursion_depth) {
  if (board_done(board)) {
    printf("Board is done after %d recursions:\n", recursion_depth);
    springerpfade++;
    print_board(board);
    return;
  } //else {printf("Working in iteration %d with board:\n", recursion_depth);print_board(board);}
  int d_x, d_y, i;
  d_x = -3; d_y = -3; i = 1;
  //printf("dx:dy\t%d\t%d\n", d_x, d_y);
  while (i == 1) {
    //printf("dx: %d\tdy: %d\t", d_x, d_y);
    if (d_x != 0 && d_y != 0) {
      if (abs(d_x) + abs(d_y) == 3) {
        if (field_exists(current_x+d_x, current_y+d_y) && board[current_x + d_x + (current_y + d_y) * N] == 0) {
          //printf("Fulfilled all parameters: dx=%d, dy=%d.\n\n", d_x, d_y);
          board[current_x + d_x + (current_y + d_y) * N] = recursion_depth;
          //print_board(board);printf("\n");
          iterate_horse_move(current_x+d_x, current_y+d_y, board, recursion_depth+1);
          board[current_x + d_x + (current_y + d_y) * N] = 0;
        } //else {printf("NF: field (%d+%d|%d+%d) does not exist or is non empty.\n", current_x, d_x, current_y, d_y);}
      } //else {printf("NF: wrong taximetric discance: %d + %d = %d\n", d_x, d_y, abs(d_x)+abs(d_y));}
    } //else {printf("NF: delta on direct connection.\n");}
    d_x = d_x + 1;
    if (d_x > 3) {d_x = -3; d_y = d_y + 1;}
    //printf("%d\n", d_y);
    if (d_y > 3) {i = 0;}
  }
  //printf("Recursion upwards!\n");
}

int main() {
  int i, start_x, start_y; time_t t;
  int* board = (int*) malloc(sizeof(int) * N * N);

  srand((unsigned) time(&t));

  start_x = rand() % N;
  start_y = rand() % N;

  for (i = 0; i < N * N; i++) {
    board[i] = 0;
  }

  board[start_x + start_y * N] = 1;
  printf("Starting with (x|y): (%d|%d)\n", start_x, start_y);
  print_board(board);
  iterate_horse_move(start_x, start_y, board, 2);
  free(board);
  printf("\nThere were %d possible solutions found for a board of size %dx%d with starting position at (%d|%d).\n", springerpfade, N, N, start_x, start_y);
  return 0;
}
