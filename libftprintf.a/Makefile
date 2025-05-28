
NAME	:= libftprintf.a

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror
INC         := -I. -I$(LIBFT_DIR)  
SRC := ft_printf.c \
       pf_putchar.c \
       pf_putstr.c \
       pf_putnbr.c \
       pf_putunbr.c \
       pf_puthex.c \
       pf_putptr.c \
	   ft_strlen.c

OBJ	:= $(SRC:.c=.o)


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

# # ---- テスト用 --------------------------------------
# TEST    := test
# TESTSRC := test.c

# $(TEST): $(NAME) $(LIBFT) $(TESTSRC)
# 	$(CC) $(CFLAGS) $(INC) $(TESTSRC) -L. -lftprintf -L$(LIBFT_DIR) -lft -o $(TEST)
# #              ^-- -L. = カレントにある libftprintf.a
# #                           ^----------- -lft  は libft.a

# run: $(TEST)
# 	./$(TEST)

# clean-test:
# 	rm -f $(TEST)

.PHONY: all clean fclean re test run clean-test
# test: $(TEST)
