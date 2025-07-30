NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Main
SRC = minishell.c \
      main_utils.c \
      main_utils_sec.c \
      signal.c

# Parsing
SRC += parse_commands.c \
       parse_commands_utils.c \
       parse_redirection_token.c \
       parse_redirection_token_utils.c \
       shell_split.c \
       split_args_with_expansion.c \
       syntax.c

# Expansion
SRC += expand_attachment.c \
       expand_environmental_variables.c \
       expand_utils.c

# Execution
SRC += execute_builtin.c \
       execute_cmd.c \
       execute_pipeline.c \
       execute_pipeline_utils.c \
       find_path.c \
       here_doc.c

# Builtins
SRC += execute_cd.c \
       execute_echo.c \
       execute_env.c \
       execute_exit.c \
       execute_export.c \
       execute_pwd.c \
       execute_unset.c \
       export_utils.c \
       get_cd_target.c

# Libft / Utils
SRC += check_something.c \
       free_tools.c \
       ft_alloc.c \
       ft_atoll.c \
       ft_is.c \
       ft_itoa.c \
       ft_mem.c \
       ft_serch.c \
       ft_split.c \
       ft_strcmp.c \
       ft_strdup.c \
       ft_put.c \
       ft_utils.c \
       is_somethings_first.c \
       is_somethings_second.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
