
#include <unistd.h>


int	main(int argc, char **argv) {
  int i;

  if (argc != 2) {
    write(1, "\n", 1);
    return (0);
  }
  i = 0;
  while (argv[1][i] && (argv[1][i] == 9 || argv[1][i] == 32))
    i++;
  if (argv[1][i] == '\0') {
    write(1, "\n", 1);
    return (0);
  }
  while (argv[1][i] && (argv[1][i] != 9 && argv[1][i] != 32)) {
    write(1, &argv[1][i], 1);
    i++;
  }
  write(1, "\n", 1);
  return (0);
}
