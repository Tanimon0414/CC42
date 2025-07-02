
NAME		= pipex
SRCS		= pipex.c \
			  pipex_utils.c
OBJS		= ${SRCS:.c=.o}


LIBFT_DIR	= libft
LIBFT		= ${LIBFT_DIR}/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I. -I${LIBFT_DIR}

RM			= rm -f


all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}:
	@make -sC ${LIBFT_DIR}

clean:
	@make -sC ${LIBFT_DIR} clean
	${RM} ${OBJS} 
fclean: clean
	@make -sC ${LIBFT_DIR} fclean
	${RM} ${NAME} 
re: fclean all

.PHONY: all clean fclean re 