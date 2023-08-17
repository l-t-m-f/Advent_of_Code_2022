#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

#define DEBUG

int my_total_score = 0;
int my_score = 0;

const int rock_score = 1;
const int paper_score = 2;
const int scissors_score = 3;

const int lose_score = 0;
const int draw_score = 3;
const int win_score = 6;

int main(void) {
  errno_t err = fopen_s(&fp, "input.txt", "r");
  if (err > 0) {
    printf("The file 'input.txt' was not opened:  %s\n", strerror(err));
    return -1;
  }
#ifdef DEBUG
  else {
    printf("The file 'input.txt' was opened\n");
  }
#endif // DEBUG

  enum { ROCK, PAPER, SCISSORS } enemy_hand, player_hand;
  enum { LOSE, DRAW, WIN } predicted_result;

  char c;
  while ((c = getc(fp)) != EOF) {
    switch (c) {
    case '\n': {
      // on newline calculate the round

      // draw
      switch (predicted_result) {
      case LOSE: {
        my_score += lose_score;
        switch (enemy_hand) {
        case ROCK: {
          player_hand = SCISSORS;
          break;
        }
        case PAPER: {
          player_hand = ROCK;
          break;
        }
        case SCISSORS: {
          player_hand = PAPER;
          break;
        }
        }
        break;
      }
      case DRAW: {
        my_score += draw_score;
        player_hand = enemy_hand;
        break;
      }
      case WIN: {
        my_score += win_score;
        switch (enemy_hand) {
        case ROCK: {
          player_hand = PAPER;
          break;
        }
        case PAPER: {
          player_hand = SCISSORS;
          break;
        }
        case SCISSORS: {
          player_hand = ROCK;
          break;
        }
        }
        break;
      }
      }

      switch (player_hand) {
      case ROCK: {
        my_score += rock_score;
        break;
      }
      case PAPER: {
        my_score += paper_score;
        break;
      }
      case SCISSORS: {
        my_score += scissors_score;
        break;
      }
      }

#ifdef DEBUG
      printf("Round score is %d\n", my_score);
#endif // DEBUG
      my_total_score += my_score;
      my_score = 0;

      break;
    }
    case 'A':
      enemy_hand = ROCK;
      break;
    case 'B':
      enemy_hand = PAPER;
      break;
    case 'C':
      enemy_hand = SCISSORS;
      break;
    case 'X':
      predicted_result = LOSE;
      break;
    case 'Y':
      predicted_result = DRAW;
      break;
    case 'Z':
      predicted_result = WIN;
      break;
    case ' ':
      // skip these
      break;
    default:
      printf("Unexpected character: %c\n", c);
      break;
    }
  }

  printf("Total score is %d\n", my_total_score);

  return 0;
}
