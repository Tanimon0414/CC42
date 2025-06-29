# -----------------------------------------------------------------------------#
#                                  VARIABLES                                   #
# -----------------------------------------------------------------------------#

# Mandatory Part
NAME		= pipex
SRCS		= pipex.c \
			  pipex_utils.c
OBJS		= ${SRCS:.c=.o}

# # Bonus Part
# NAME_BONUS	= pipex_bonus
# SRCS_BONUS	= pipex_bonus.c
# OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

# Libft
LIBFT_DIR	= libft
LIBFT		= ${LIBFT_DIR}/libft.a

# Compilation
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I. -I${LIBFT_DIR}

# Cleanup
RM			= rm -f

# -----------------------------------------------------------------------------#
#                                     RULES                                    #
# -----------------------------------------------------------------------------#

# Default rule: builds the mandatory executable
all: ${NAME}

# Builds the mandatory executable
${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

# Generic rule to compile .c files into .o files
%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

# Builds the libft library
${LIBFT}:
	@make -sC ${LIBFT_DIR}

# Rule to build the bonus executable
# bonus: ${NAME_BONUS}

# Builds the bonus executable
# ${NAME_BONUS}: ${OBJS_BONUS} ${LIBFT}
# 	${CC} ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

# Cleans object files from the main project and libft
clean:
	@make -sC ${LIBFT_DIR} clean
	${RM} ${OBJS} 
# ${OBJS_BONUS}

# Cleans all compiled files (executables and objects) from main project and libft
fclean: clean
	@make -sC ${LIBFT_DIR} fclean
	${RM} ${NAME} 
# ${NAME_BONUS}

# Re-compiles the entire project from scratch
re: fclean all

# Phony rules prevent conflicts with files of the same name
.PHONY: all clean fclean re bonus