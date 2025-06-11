
NAME        := push_swap

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCS        := -I.                     # ヘッダがあるディレクトリを追加する場合はここに追記

RM          := rm -f

### ソース一覧 ###
SRCS := \
	check.c \
	commands_p.c \
	commands_r.c \
	commands_rr.c \
	commands_s.c \
	count_commands.c \
	error.c \
	init_commands.c \
	init_stacks.c \
	index.c \
	main.c \
	sort_small.c \
	sort_stacks.c \
	sort_utils.c \
	utils.c

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
