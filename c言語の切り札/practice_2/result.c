#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DIGITS 4
#define TRUE 1
#define FALSE 2

void createRandomNumber(char[]);
int isValidNumber(char[]);
void GuessNumber();
int isMatch(char[], char[]);
void showTitle(void);

int main(int argc, char const *argv[]) {
  GuessNumber();
  return 0;
}

void GuessNumber() {
  char target[DIGITS + 1]; /* 目標数の保存領域 */
  char num[DIGITS + 1];    /* 推測数の保存領域 */
  int count = 0;           /* 推測回数 */

  showTitle();
  createRandomNumber(target); /* 目標数の生成 */
  do {
    printf(
        "[%d回目]各桁が異なる%d桁の数を入力してください:\n", ++count, DIGITS);
    scanf("%4s", num);

    while (isValidNumber(num) == FALSE) {
      printf("同じ数字は入力できません。再度入力してください:\n");
      scanf("%4s", num);
    }
  } while (strcmp(num, "quit") != 0 && isMatch(target, num) == FALSE);
  printf("正解は、%sです。\n", target);
  exit(0);
}

void showTitle(void) {
  printf("==============\n");
  printf(" 数当てゲーム \n");
  printf("==============\n");
  printf(
      "プログラムが生成した各桁の数字が異なる%d"
      "桁の目標数を、なるべく少ない回数の推測で当てるゲームGuessNumberです。"
      "\n",
      DIGITS);
  printf("ギブアップの場合は、「quit」と入力してください。\n");
  printf("では、スタートします。\n");
  for (int i = 0; i < 4; i++) {
    printf("目標数を設定中");
    for (int j = 0; j < i; j++) printf("・");
    puts("");
    printf("\033[2K\033[G\n");
    printf("\033[2F");
    fflush(stdout);
    (void)sleep(1);
    printf("\033[2K");
  }
  printf("目標数の設定完了\n");
}

void createRandomNumber(char target[]) {
  char base[10]    = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  unsigned int now = (unsigned int)time(0);
  srand(now);
  for (int i = 0; i < DIGITS; i++) {
    int j   = rand() % 10;
    int t   = base[j];
    base[j] = base[i];
    base[i] = t;
  }
  for (int i = 0; i < DIGITS; i++) target[i] = base[i];
}

int isValidNumber(char num[]) {
  char t;
  for (int i = 0; i < DIGITS; i++) {
    t = num[i];
    for (int j = i + 1; j < DIGITS; j++)
      if (t == num[j]) return FALSE;
  }
  return TRUE;
}

int isMatch(char target[], char num[]) {
  int numHit = 0, numBlow = 0;

  for (int i = 0; i < DIGITS; i++) {
    for (int j = 0; j < DIGITS; j++) {
      if (num[i] == target[j]) {
        if (i == j) {
          numHit++;
        } else {
          numBlow++;
        }
      }
    }
  }

  if (numHit == DIGITS) {
    printf("正解です\n");
    return TRUE;
  }
  printf("%sは%dHit, %dBlowです。\n\n", num, numHit, numBlow);
  return FALSE;
}
