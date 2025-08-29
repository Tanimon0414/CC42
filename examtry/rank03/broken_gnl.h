#ifndef BROKEN_GNL
# define BROKEN_GNL

# include <stdlib.h> // ここがなかった
# include <unistd.h> // ここがなかった

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char    *get_next_line(int fd);

#endif