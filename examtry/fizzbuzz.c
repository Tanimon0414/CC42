
#include <unistd.h>


void	ft_putchar(char c) {
  write(1, &c, 1);
  return ;
}

void	ft_putnbr(int i) {
  if (i >= 10)
    ft_putnbr(i / 10);
  ft_putchar(i % 10 + '0');
}

int	main(void) {
  int i;

  i = 1;
  while (i <= 100) {
    if (i % 15 == 0)
      write(1, "fizzbuzz\n", 9);
    else if (i % 3 == 0)
      write(1, "fizz\n", 5);
    else if (i % 5 == 0)
      write(1, "buzz\n", 5);
    else {
      ft_putnbr(i);
      write(1, "\n", 1);
    }
    i++;
  }
  return (0);
}
