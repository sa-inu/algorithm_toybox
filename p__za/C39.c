#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char code[100];
  const char TEN_SYM = '<', ONE_SYM = '/', PLUS_SYM = '+';
  int len, sum = 0, num = 0;

  scanf("%s", code);
  len = strlen(code);

  for (int i = 0; i < len; i++) {
    if (code[i] == TEN_SYM) {
      num += 10;
    } else if (code[i] == ONE_SYM) {
      num++;
    } else if (code[i] == PLUS_SYM) {
      sum += num;
      num = 0;
    } else {
      printf("読み取れない文字が入力されました\n");
      break;
    }

    if (i == len - 1)
      sum += num;
  }

  printf("%d\n", sum);

  return 0;
}
