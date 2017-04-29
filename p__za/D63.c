#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define REI 'A'
#define HAKUSYU 'B'

int main(int argc, char const *argv[]) {
  char input[63], *data, output;
  int n, isREI = TRUE;

  scanf("%[^\n]", input); // 1 2 3

  data = strtok(input, " ");
  while (data != NULL) {
    output = isREI ? REI : HAKUSYU;
    for (int i = 0; i < atoi(data); i++)
      printf("%c", output);
    isREI = isREI ? FALSE : TRUE;
    data = strtok(NULL, " ");
  }
  puts("");
  // output: ABBAAA

  return 0;
}
