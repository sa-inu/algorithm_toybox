一番下に参考プログラムあり。

![](https://i.gyazo.com/bd1119b434d1b0cac7a9c597232da06d.png)
![](https://i.gyazo.com/f28cc2aab13d6a9be419fe33903a0d71.png)
![](https://i.gyazo.com/d0fd68c233a3337f37c2512f59c5bc8b.png)

```
#include <stdio.h>

#define DIGITS 4
#define TRUE 1
#define FALSE 2

void createRandomNumber(char[]);
int isValidNumber(char[]);
void GuessNumber();
int isMatch(char[], char[]);

void GuessNumber() {
  char target[DIGITS + 1]; /* 目標数の保存領域 */
  char num[DIGITS + 1];    /* 推測数の保存領域 */
  int count = 0;           /* 推測回数 */

  createRandomNumber(target); /* 目標数の生成 */
  do {
    printf("[%d回目]各桁が異なる%d桁の数を入力してください:\n", ++count, DIGITS);
    scanf("%4s", num);

    while ([FILL ME IN]) {
      printf("入力が正しくありません。再度入力してください:\n");
      scanf("%4s", num);
    }
  } while ([FILL ME IN]);
}

int isMatch(char target[], char num[]) {
  int numHit = 0, numBlow = 0;

  for (int i = 0; i < DIGITS; i++) {
    for (int j = 0; j < DIGITS; j++) {
      if ([FILL ME IN]) {
        if ([FILL ME IN]) {
          numHit++;
        } else {
          numBlow++;
        }
      }
    }
  }

  if ([FILL ME IN]) {
    printf("正解です\n");
    return TRUE;
  }
  printf("%sは%dHit, %dBlowです。\n\n", num, numHit, numBlow);
  return FALSE;
}
```
