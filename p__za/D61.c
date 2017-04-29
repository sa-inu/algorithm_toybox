#include <stdio.h>

int main(int argc, char const *argv[]) {
  char c_1, c_2;

  scanf("%c %c", &c_1, &c_2);

  if (c_1 == 'J' && c_2 == 'J')
    c_2 = 'Q';

  printf("%c %c\n", c_1, c_2);

  return 0;
}
