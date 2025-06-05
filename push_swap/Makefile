
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME_MANDATORY = push_swap
NAME_BONUS = checker


#--- Libft Configuration ---
LIBFT_DIR = libft/
LIBFT_A = $(LIBFT_DIR)libft.a
LIBFT_MAKE_COMMAND = $(MAKE) -C $(LIBFT_DIR) all

#--- Include ---
INCLUDES = -I$(LIBFT_DIR)

#--- Sources Files for push_swap and checker ---
SRCS_MANDATORY = 
# SRCS_BONUS = 
# TEST_SRCS_PS = test.c

#--- Object Files ---
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS     = $(SRCS_BONUS:.c=.o)
# TEST_OBJS_PS   = $(TEST_SRCS_PS:.c=.o)

#--- Test Program Name ---
# TEST_NAME_PS = test_ps # push_swap のテスト実行ファイル名

all: $(NAME_MANDATORY)

$(LIBFT_A):
		@echo "Building Libft (including ft_printf and bonus functions)..."
		@$(LIBFT_MAKE_COMMAND)

$(NAME_MANDATORY): $(OBJS_MANDATORY) $(LIBFT_A)
		@echo "Compiling $(NAME_MANDATORY)..."
		$(CC) $(CFGLASS) $(INCLUDES) $(OBJS_MANDATORY) $(LIBFT_A) -o $(NAME_BONUS)
		@echo "$(TEST_NAME_PS) compiled!"

clean:
		@echo "Cleaning push_swap object files..."
		$(RM) $(OBJS_MANDATORY) $(OBJS_BONUS) $(TEST_OBJS_PS)
		@echo "Cleaning Libft..."
		@$(MAKE) -C $(LIBFT_DIR) clean 
	
fclean: clean
		@echo "Cleaning $(NAME_MANDATORY), $(NAME_BONUS), and test program..."
		$(RM) $(NAME_MANDATORY) $(NAME_BONUS) $(TEST_NAME_PS)
		@echo "Full cleaning Libft..."
		@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY all clean fclean re  libft
# bonus test