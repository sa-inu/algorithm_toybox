#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 22
#define MINO_WIDTH 4
#define MINO_HEIGHT 4
#define TRUE 1
#define FALSE 0

/* Custom Library */
void init_keyboard(void);
void close_keyboard(void);
int kbhit();
int readkey();
static struct termios init_tio;
/* Custom Library */

void render(void);
int isHit(int, int, int, int);
void deleteLine(void);
void resetMino(void);

char field[FIELD_HEIGHT][FIELD_WIDTH] = {0};
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH] = {0};
int minoType = 0, minoAngle = 0;
int minoX = 5, minoY = 0;

enum {
  MINO_TYPE_I,
  MINO_TYPE_O,
  MINO_TYPE_S,
  MINO_TYPE_Z,
  MINO_TYPE_J,
  MINO_TYPE_L,
  MINO_TYPE_T,
  MINO_TYPE_MAX
};

enum {
  MINO_ANGLE_0,
  MINO_ANGLE_90,
  MINO_ANGLE_180,
  MINO_ANGLE_270,
  MINO_ANGLE_MAX
};

// clang-format off
char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] = {
  /* MINO_TYPE_I */
  {
    /* MINO_ANGLE_0 */
    {
      { 0, 1, 0, 0 },
      { 0, 1, 0, 0 },
      { 0, 1, 0, 0 },
      { 0, 1, 0, 0 },
    },
    /* MINO_ANGLE_90 */
    {
      { 0, 0, 0, 0 },
      { 1, 1, 1, 1 },
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
    },
    /* MINO_ANGLE_180 */
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
    },
    /* MINO_ANGLE_270 */
    {
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      { 1, 1, 1, 1 },
      { 0, 0, 0, 0 },
    },
    /* MINO_ANGLE_MAX */
  },
  /* MINO_TYPE_O */
  {
    /* MINO_ANGLE_0 */
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    /* MINO_ANGLE_90 */
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    /* MINO_ANGLE_180 */
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    /* MINO_ANGLE_270 */
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    /* MINO_ANGLE_MAX */
  },
  /* MINO_TYPE_Z */
  {
    // MINO_ANGLE_0
    {
      { 0, 0, 0, 0 },
      { 1, 1, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_90
    {
      { 0, 0, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 0, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_180
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 1 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_270
    {
      { 0, 0, 0, 0 },
      { 0, 0, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 0, 0 }
    }
    // MINO_ANGLE_MAX
  },
  /* MINO_TYPE_S */
  {
    // MINO_ANGLE_0
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 1, 1, 0, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_90
    {
      { 0, 1, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_180
    {
      { 0, 0, 0, 0 },
      { 0, 0, 1, 1 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_270
    {
      { 0, 0, 0, 0 },
      { 0, 1, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 0 }
    },
    // MINO_ANGLE_MAX
  },
  /* MINO_TYPE_J */
  {
    // MINO_ANGLE_0
    {
      { 0, 0, 0, 0 },
      { 1, 1, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_90
    {
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_180
    {
      { 0, 0, 0, 0 },
      { 0, 1, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_270
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 0, 0 },
      { 0, 1, 0, 0 }
    }
    // MINO_ANGLE_MAX
  },
  /* MINO_TYPE_L */
  {
    // MINO_ANGLE_0
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 1, 0, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_90
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 0 },
      { 0, 0, 1, 0 }
    },
    // MINO_ANGLE_180
    {
      { 0, 0, 0, 0 },
      { 0, 0, 1, 0 },
      { 1, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_270
    {
      { 0, 1, 0, 0 },
      { 0, 1, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_MAX
  },
  /* MINO_TYPE_T */
  {
    // MINO_ANGLE_0
    {
      { 0, 0, 0, 0 },
      { 0, 1, 0, 0 },
      { 1, 1, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_90
    {
      { 0, 1, 0, 0 },
      { 0, 1, 1, 0 },
      { 0, 1, 0, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_180
    {
      { 0, 0, 0, 0 },
      { 0, 1, 1, 1 },
      { 0, 0, 1, 0 },
      { 0, 0, 0, 0 }
    },
    // MINO_ANGLE_270
    {
      { 0, 0, 0, 0 },
      { 0, 0, 1, 0 },
      { 0, 1, 1, 0 },
      { 0, 0, 1, 0 }
    },
    // MINO_ANGLE_MAX
  }
  /* MINO_TYPE_MAX */
};
// clang-format on

int main(int argc, char const *argv[]) {
  for (int i = 0; i < FIELD_HEIGHT; i++)
    field[i][0] = field[i][FIELD_WIDTH - 1] = 1;
  for (int i = 0; i < FIELD_WIDTH; i++)
    field[FIELD_HEIGHT - 1][i] = 1;

  resetMino();

  char input;
  time_t baseTime = time(NULL), nowTime;
  init_keyboard();
  while (1) {
    if (kbhit()) {
      input = (char)readkey();
      switch (input) {
      case '\n':
        while (!isHit(minoX, minoY + 1, minoType, minoAngle))
          minoY++;
        break;
      case 'j': // d: 落下
        if (!isHit(minoX, minoY + 1, minoType, minoAngle))
          minoY++;
        break;
      case 'h': // h: 左
        if (!isHit(minoX - 1, minoY, minoType, minoAngle))
          minoX--;
        break;
      case 'l': // l: 右
        if (!isHit(minoX + 1, minoY, minoType, minoAngle))
          minoX++;
        break;
      case 'o': // o: 変換
        if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX))
          minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
        break;
      default:
        break;
      }
      render();
    }

    if (baseTime != (nowTime = time(NULL))) {
      if (isHit(minoX, minoY + 1, minoType, minoAngle)) {
        for (int i = 0; i < MINO_HEIGHT; i++)
          for (int j = 0; j < MINO_WIDTH; j++)
            field[minoY + i][minoX + j] |=
              minoShapes[minoType][minoAngle][i][j];
        deleteLine();
        for (int i = 1; i < FIELD_WIDTH - 1; i++) {
          if (field[0][i] == TRUE) {
            system("cls");
            printf("----END----\n");
            return 1;
          }
        }
        resetMino();
      } else
        minoY++;
      render();
      baseTime = nowTime;
    }
  }
  close_keyboard();

  return 0;
}

void resetMino(void) {
  minoX = 5;
  minoY = 0;
  minoType = rand() % MINO_TYPE_MAX;
  minoAngle = rand() % MINO_ANGLE_MAX;
}

void render(void) {
  memcpy(displayBuffer, field, sizeof(field));

  for (int i = 0; i < MINO_HEIGHT; i++)
    for (int j = 0; j < MINO_WIDTH; j++)
      displayBuffer[minoY + i][minoX + j] |=
        minoShapes[minoType][minoAngle][i][j];

  system("cls");

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++)
      printf(displayBuffer[i][j] ? "■ " : "　");
    printf("\n");
  }
}

int isHit(int _minoX, int _minoY, int _minoType, int _minoAngle) {
  for (int i = 0; i < MINO_HEIGHT; i++)
    for (int j = 0; j < MINO_WIDTH; j++)
      if (minoShapes[_minoType][_minoAngle][i][j] &&
          field[_minoY + i][_minoX + j])
        return TRUE;
  return FALSE;
}

void deleteLine(void) {
  int lineFill;
  for (int i = 0; i < FIELD_HEIGHT - 1; i++) {
    lineFill = TRUE;
    for (int j = 1; j < FIELD_WIDTH - 1; j++)
      if (!field[i][j])
        lineFill = FALSE;
    if (lineFill)
      for (int j = i; 0 < j; j--)
        memcpy(field[j], field[j - 1], FIELD_WIDTH);
  }
}

/* Custom Library */
void init_keyboard(void) { tcgetattr(0, &init_tio); }
void close_keyboard(void) { tcsetattr(0, TCSANOW, &init_tio); }
int kbhit(void) {
  struct termios tio;
  struct timeval tv;
  fd_set rfds;
  // set up terminal
  memcpy(&tio, &init_tio, sizeof(struct termios));
  tio.c_lflag &= ~(ICANON);
  tcsetattr(0, TCSANOW, &tio);
  // do not wait
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);
  tv.tv_usec = 0;
  tv.tv_sec = 0;
  select(1, &rfds, NULL, NULL, &tv);
  // back to initial terminal mode
  tcsetattr(0, TCSANOW, &init_tio);
  return (FD_ISSET(0, &rfds) ? 1 : 0);
}
int readkey(void) {
  int ch;
  struct termios tio;
  // set up terminal
  memcpy(&tio, &init_tio, sizeof(struct termios));
  tio.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
  // input key
  read(0, &ch, 1);
  // back to initial terminal mode
  tcsetattr(0, TCSANOW, &init_tio);
  return ch;
}
/* Custom Library */
