NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = execute_builtin.c ft_utils.c minishell.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
