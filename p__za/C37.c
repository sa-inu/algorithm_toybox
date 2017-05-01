#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
  char *date = "01/27 24:30";
  struct tm tm;

  scanf("%d/%d %d:%d", &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min);

  while (tm.tm_hour > 23) {
    tm.tm_hour = tm.tm_hour - 24;
    tm.tm_mday++;
  }

  printf("%02d/%02d %02d:%02d\n", tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);

  return 0;
}
