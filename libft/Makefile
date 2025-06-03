
NAME	= libft.a
CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I. -Ift_printf_srcs

SRCS_LIBFT	= ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
	ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
	ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
	ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memmove.c \
	ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c ft_toupper.c \
	ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c ft_putstr_fd.c \
	ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c

PRINTF_DIR = ft_printf_srcs
SRCS_PRINTF = $(PRINTF_DIR)/ft_printf.c \
       $(PRINTF_DIR)/pf_putchar.c \
       $(PRINTF_DIR)/pf_putstr.c \
       $(PRINTF_DIR)/pf_putnbr.c \
       $(PRINTF_DIR)/pf_putunbr.c \
       $(PRINTF_DIR)/pf_puthex.c \
       $(PRINTF_DIR)/pf_putptr.c 


BONUS_SRCS_LIBFT	= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstmap.c

SRCS_ALL = $(SRCS_LIBFT) $(SRCS_PRINTF) $(BONUS_SRCS_LIBFT)


OBJS_ALL	= $(SRCS_ALL:.c=.o)

#--- テスト用設定 ---
TEST_SRC = test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_NAME = test_printf

all: $(NAME)

$(NAME): $(OBJS_ALL)
	@ar rcs $(NAME) $(OBJS_ALL)
	@echo "Library $(NAME) created with all features (Libft mandatory, ft_printf, Libft bonus)."
	@echo "Included objects: $(notdir $(OBJS_ALL))"

bonus: all
		@echo "$(NAME) including all features is ready (built via 'all' target)."

%.o: %.c libft.h ft_printf.h
		$(CC) $(CFLAGS) -c $< -o $@

#--- テスト用コンパイルルール ---
$(TEST_OBJ): $(TEST_SRC) libft.h ft_printf.h $(NAME)
		$(CC) $(CFGLASS) -c $(TEST_SRC) -o $(TEST_OBJ)

$(TEST_NAME): $(TEST_OBJ) $(NAME)
		$(CC) $(CFLAGS) $(TEST_OBJ) -L. -lft -o $(TEST_NAME)

#--- クリーンルール ---

clean:
	rm -f $(OBJS_ALL) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

#--- テスト実行用ルール ---
test: $(TEST_NAME)
		@echo "Running $(TEST_NAME)..."
		./$(TEST_NAME)

.PHONY: all clean fclean re bonus test