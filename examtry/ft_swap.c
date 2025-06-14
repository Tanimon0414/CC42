
void	ft_swap(int *a, int *b) {
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

#include <stdio.h>


int	main(void) {
  int x;
  int y;

  x = 4;
  y = 2;
  printf("%d,%d\n", x, y);
  ft_swap(&x, &y);
  printf("%d,%d\n", x, y);
  return (0);
}
