
#include <unistd.h>


int	ft_strlen(char *str) {
  int i;
  i = 0;
  while (str[i])
    i++;
  return (i);
}

int	main(int argc, char **argv) {
  int i;
  int j;
  i = 0;
  j = 0;
  if (argc == 3) {
    while (argv[1][i] && argv[2][j]) {
      if (argv[1][i] == argv[2][j])
        i++;
      j++;
    }
    if (argv[1][i]) {
      write(1, "\n", 1);
      return (0);
    }
    int len;
    len = ft_strlen(argv[1]);
    write(1, argv[1], len);
  }
  write(1, "\n", 1);
  return (0);
}
