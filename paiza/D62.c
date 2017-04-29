#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char dolls[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  char input[5], *count;
  int start = 0, end;

  scanf("%[^\n]", input); // 2 3 5

  count = strtok(input, " ");
  while (count != NULL) {
    end = start + atoi(count);
    for (int i = start; i < end; i++)
      printf("%c", dolls[i]);
    puts("");
    start = end;
    count = strtok(NULL, " ");
  }
  // output:
  // AB
  // CDE
  // FGHIJ
  return 0;
}
