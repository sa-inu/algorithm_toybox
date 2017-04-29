#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char input[16];
  char *time;
  int a;
  int turn = 1;

  scanf("%[^\n]", input); // 0 10 23 35 57
  scanf("%d", &a);        // 29

  time = strtok(input, " ");
  while (time != NULL) {
    if (atoi(time) < a)
      turn++;
    else
      break;
    time = strtok(NULL, " ");
  }

  printf("%d\n", turn); // 4
}
