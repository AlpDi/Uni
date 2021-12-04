#include <stdio.h>
#include <stdlib.h>

// with n element of {5, 6} being the length of the sides
#define N 5

#define FIELD_START 2
#define FIELD_EMPTY 0
#define FIELD_MARKED 1

void print_board(int board[]) {
  int i;
  for (i = 0; i < (N * N); i++) {
    printf("%d", board[i]);
    // printf("(i / N): %d\t(N - 1): %d\t `==`: %d\n", (i / N), (N - 1), ((i / N) == (N - 1)));
    if ((i + 1) % N == 0) {
      printf("\n");
    } else {
      printf("\t");
    }
  }
  // printf("\ni: %d\n\n", i);
}

int board_done(int board[]) {
  int i;
  for (i = 0; i < N * N; i++) {
    if (board[i] == 1) {} else {
      return 0;
    }
  }
  return 1;
}

int field_exists(x, y) {
  if (x < 0) {return 0;}
  if (y < 0) {return 0;}
  if (x >= N) {return 0;}
  if (y >= N) {return 0;}
  return 1;
}

void iterate_horse_move(int current_x, int current_y, int board[]) {
  board[current_x + current_y * N] = 1;
  if (board_done(board)) {
    printf("Board is done:\n");
    print_board(board);
    return;
  }
  if (field_exists(current_x-1, current_y-2)) {
    iterate_horse_move(current_x-1, current_y-2, board);
  }
  if (field_exists(current_x+1, current_y-2)) {
    iterate_horse_move(current_x+1, current_y-2, board);
  }
  if (field_exists(current_x+2, current_y-1)) {
    iterate_horse_move(current_x+2, current_y-1, board);
  }
  if (field_exists(current_x+2, current_y+1)) {
    iterate_horse_move(current_x+2, current_y+1, board);
  }
  if (field_exists(current_x+1, current_y+2)) {
    iterate_horse_move(current_x+1, current_y+2, board);
  }
  if (field_exists(current_x-2, current_y+2)) {
    iterate_horse_move(current_x-2, current_y+2, board);
  }
  if (field_exists(current_x-2, current_y+1)) {
    iterate_horse_move(current_x-2, current_y+1, board);
  }
  if (field_exists(current_x-2, current_y-1)) {
    iterate_horse_move(current_x-2, current_y-1, board);
  }
}

int main() {
  int i, x, y, start_x, start_y; time_t t;
  int* board = (int*) malloc(sizeof(int) * N * N);

  srand((unsigned) time(&t));

  start_x = rand() % N;
  start_y = rand() % N;

  for (i = 0; i < N * N; i++) {
    x = i % N; y = i / N;
    if (x == start_x && y == start_y) {
      board[i] = 2;
    } else {
      board[i] = 0;
    }
    // printf("x: %d\ty: %d\ti: %d\tboard[i]: %d\n", x, y, i, board[i]);
  }
  printf("Starting with (x|y): (%d|%d)\n\n", start_x, start_y);
  print_board(board);
  iterate_horse_move(start_x, start_y, board);
  free(board);
  return 0;
}
