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
  } highest_scores[3];
  while (!feof(fp)) {
    char line[256];
    fgets(line, 256, fp);
    running_total += atoi(line);
    if (line[0] == '\n') {
      elf++;
      if (running_total > highest_scores[0].calories) {

        highest_scores[2].elf = highest_scores[1].elf;
        highest_scores[2].calories = highest_scores[1].calories;

        highest_scores[1].elf = highest_scores[0].elf;
        highest_scores[1].calories = highest_scores[0].calories;

        highest_scores[0].elf = elf;
        highest_scores[0].calories = running_total;
      } else if (running_total > highest_scores[1].calories) {

        highest_scores[2].elf = highest_scores[1].elf;
        highest_scores[2].calories = highest_scores[1].calories;

        highest_scores[1].elf = elf;
        highest_scores[1].calories = running_total;

      } else if (running_total > highest_scores[2].calories) {

        highest_scores[2].elf = highest_scores[1].elf;
        highest_scores[2].calories = running_total;
      }
#ifdef DEBUG
      printf("Elf %d carried %d calories\n", elf, running_total);
#endif // DEBUG
      running_total = 0;
    }
  }
  printf("Top 3 Elves carrying the most calories: \n %d carries %d\n %d "
         "carries %d\n %d carries %d\n",
         highest_scores[0].elf, highest_scores[0].calories,
         highest_scores[1].elf, highest_scores[1].calories,
         highest_scores[2].elf, highest_scores[2].calories);

  int absolute_total = 0;
  for (int i = 0; i < 3; i++) {
    absolute_total += highest_scores[i].calories;
  }

  printf("Absolute total: %d\n", absolute_total);

  return 0;
}