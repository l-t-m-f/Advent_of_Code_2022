#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

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
  int elf = 0;
  int running_total = 0;
  struct {
    int elf;
    int calories;
  } highest_score;
  while (!feof(fp)) {
    char line[256];
    fgets(line, 256, fp);
    running_total += atoi(line);
    if (line[0] == '\n') {
      elf++;
      if (running_total > highest_score.calories) {
        highest_score.elf = elf;
        highest_score.calories = running_total;
      }
#ifdef DEBUG
      printf("Elf %d carried %d calories\n", elf, running_total);
#endif // DEBUG
      running_total = 0;
    }
  }
  printf("Elf %d carried the most calories: %d\n", highest_score.elf,
         highest_score.calories);
  return 0;
}