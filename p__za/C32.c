#include <stdio.h>

typedef struct thing {
  int type;
  int price;
} thing_t;

typedef struct product {
  int type;
  int point;
  int sum;
} product_t;

int main(int argc, char const *argv[]) {
  int food_count;
  int type, price;
  int points = 0;
  product_t food = {0, 5, 0};
  product_t book = {1, 3, 0};
  product_t close = {2, 2, 0};
  product_t other = {3, 1, 0};

  scanf("%d", &food_count);
  for (int i = 0; i < food_count; i++) {
    scanf("%d %d", &type, &price);
    if (type == food.type)
      food.sum += price / 100 * food.point;
    else if (type == book.type)
      book.sum += price / 100 * book.point;
    else if (type == close.type)
      close.sum += price / 100 * close.point;
    else if (type == other.type)
      other.sum += price / 100 * other.point;
  }

  points = food.sum + book.sum + close.sum + other.sum;

  printf("%d\n", points);

  return 0;
}
