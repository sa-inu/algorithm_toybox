#include <stdio.h>
#define RSZ 6
#define CSZ 8

void invert(int invtype, char in[CSZ][RSZ]) {
  int row = RSZ, col = CSZ;
  int i, j;

  if (invtype == 1 || invtype == 2) {
    row = CSZ;
    col = RSZ;
  }
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < row; j++) {
      switch (invtype) {
        case 1: /* 90度右回転 */
          printf("%c", in[CSZ - j - 1][i]);
          break;
        case 2: /* 90度左回転 */
          printf("%c", in[j][RSZ - i - 1]);
          break;
        case 3: /* 上下反転 */
          printf("%c", in[CSZ - i - 1][j]);
          break;
        case 4: /* 左右反転 */
          printf("%c", in[i][RSZ - j - 1]);
          break;
        default:
          break;
      }
    }
    printf("\n");
  }
}

int main(int argc, char const *argv[]) {
  char src[CSZ][RSZ] = {{'#', '#', '#', '#', '#', '#'},
                        {'#', ' ', ' ', ' ', ' ', ' '},
                        {'#', ' ', ' ', ' ', ' ', ' '},
                        {'#', ' ', ' ', ' ', ' ', ' '},
                        {'#', '#', '#', ' ', ' ', ' '},
                        {'#', ' ', ' ', ' ', ' ', ' '},
                        {'#', ' ', ' ', ' ', ' ', ' '},
                        {'#', ' ', ' ', ' ', ' ', ' '}};
  invert(1, src);
  invert(2, src);
  invert(3, src);
  invert(4, src);
  return 0;
}
