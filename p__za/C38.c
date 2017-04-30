#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct machine {
  int no;                 // 機械の番号
  int containers_count;   // 容器の数
  int division_remainder; // 余り
} MACHINE;

int comp(const void *m_1, const void *m_2) {
  MACHINE machine_1 = *(MACHINE *)m_1;
  MACHINE machine_2 = *(MACHINE *)m_2;

  int tmp1 = machine_1.containers_count;
  int tmp2 = machine_2.containers_count;

  return tmp2 - tmp1;
}

int main(int argc, char const *argv[]) {
  int machines_count, snacks_count, flag;
  MACHINE machines[100];
  MACHINE tmp;
  MACHINE object;

  scanf("%d %d", &machines_count, &snacks_count);
  for (int i = 0; i < machines_count; i++) {
    machines[i].no = i + 1;
    scanf("%d", &machines[i].containers_count);
    machines[i].division_remainder =
      snacks_count % machines[i].containers_count;
  }

  qsort(machines, machines_count, sizeof(MACHINE), comp);

  for (int i = 0; i < machines_count; i++) {
    flag = TRUE;
    for (int j = i + 1; j < machines_count; j++) {
      if (machines[i].division_remainder > machines[j].division_remainder) {
        flag = FALSE;
        break;
      }
    }
    if (flag) {
      object = machines[i];
      break;
    }
  }

  printf("%d\n", object.no);

  return 0;
}
