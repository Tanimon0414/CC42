
NAME        := push_swap

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCS        := -I.                     # ヘッダがあるディレクトリを追加する場合はここに追記

RM          := rm -f

### ソース一覧 ###
SRCS := \
	00_main.c \
	01_input_parsing.c \
	02_stack_init.c \
	03_node_utils.c \
	04_operations_push.c \
	05_operations_swap.c \
	06_operations_rotate.c \
	07_operations_rev_rotate.c \
	08_sort_controller.c \
	09_sort_small.c \
	10_cost_calculation.c \
	11_target_position.c \
	12_sort_utils.c \
	13_utils.c \
	99_error.c

OBJS := $(SRCS:.c=.o)

### libft ###
LIBFT_DIR := libft
LIBFT     := $(LIBFT_DIR)/libft.a

### ルール ###
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
