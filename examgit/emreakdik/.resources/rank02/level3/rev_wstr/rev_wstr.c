
#include <unistd.h>


void	ft_putchar(char c) { write(1, &c, 1); }

int	ft_strlen(char *str) {
  int i = 0;

  while (str[i])
    i++;
  return (i);
}

int	main(int ac, char *av[]) {
  char *tmp;
  char *rev;
  int len;

  if (ac == 2) {
    tmp = av[1];
    len = ft_strlen(tmp);
    rev = NULL;
    len--;
    while (tmp[len]) {
      if (tmp[len - 1] == ' ') {
        rev = &tmp[len];
        while (*rev && *rev != ' ') {
          ft_putchar(*rev);
          rev++;
        }
        ft_putchar(' ');
      } else if (len == 0) {
        rev = &tmp[len];
        while (*rev && *rev != ' ') {
          ft_putchar(*rev);
          rev++;
        }
      }
      len--;
    }
  }
  ft_putchar('\n');
}
