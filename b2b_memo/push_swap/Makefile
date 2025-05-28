NAME = push_swap

CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE_PATH = include/
SRC_PATH = src/
LIBFT_PATH = Libft/

INCLUDE = $(INCLUDE_PATH)push_swap.h
SRC_FILES = main.c \
			util.c \
			stack_util.c \
			node_util.c \
			atol.c \
			sort.c \
			small_sort.c \
			swap.c \
			push.c \
			rotate.c \
			reverse_rotate.c \
			index_util.c \
			radix_sort.c
SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(SRC:.c=.o)
LIBFT = $(LIBFT_PATH)libft.a

all: $(NAME)
$(NAME): $(INCLUDE) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c $(INCLUDE) $(LIBFT)
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	rm -rf  $(OBJ) $(CHECKER_OBJ)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	rm -rf  $(NAME) $(CHECKER)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
