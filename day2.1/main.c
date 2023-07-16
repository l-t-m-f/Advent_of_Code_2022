#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

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

  enum { Rock, Paper, Scissors } enemy_p, player;

  char c;
  while ((c = getc(fp)) != EOF) {
    switch (c) {
    case '\n':

      // on newline calculate the round

      // draw
      if (enemy_p == player) {
        my_score += draw_score;
        switch (player) {
        case Rock:
          my_score += rock_score;
          break;
        case Paper:
          my_score += paper_score;
          break;
        case Scissors:
          my_score += scissors_score;
          break;
        }

        // player loses
      } else if (enemy_p == Rock && player == Scissors) {
        my_score += lose_score;
        my_score += scissors_score;
      } else if (enemy_p == Paper && player == Rock) {
        my_score += lose_score;
        my_score += rock_score;
      } else if (enemy_p == Scissors && player == Paper) {
        my_score += lose_score;
        my_score += paper_score;

        // player wins
      } else if (enemy_p == Rock && player == Paper) {
        my_score += win_score;
        my_score += paper_score;
      } else if (enemy_p == Paper && player == Scissors) {
        my_score += win_score;
        my_score += scissors_score;
      } else if (enemy_p == Scissors && player == Rock) {
        my_score += win_score;
        my_score += rock_score;
      }
#ifdef DEBUG
      printf("Round score is %d\n", my_score);
#endif // DEBUG
      my_total_score += my_score;
      my_score = 0;

      break;
    case 'A':
      enemy_p = Rock;
      break;
    case 'B':
      enemy_p = Paper;
      break;
    case 'C':
      enemy_p = Scissors;
      break;
    case 'X':
      player = Rock;
      break;
    case 'Y':
      player = Paper;
      break;
    case 'Z':
      player = Scissors;
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
