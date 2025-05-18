# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 11:49:07 by kishigam          #+#    #+#              #
#    Updated: 2022/06/12 13:55:53 by kishigam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCS_DIR	= ./includes

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCS		= -I$(INCS_DIR) -I$(LIBFT_DIR)
LFLAGS		= -L$(LIBFT_DIR) -lft
LIB			= ar -rcs
RM			= /bin/rm -f

SRC_DIR		= ./srcs
SRCS        = $(SRC_DIR)/ft_printf.c \
            $(SRC_DIR)/ft_setting.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

.c.o: 		
			$(CC) $(CFLAGS) $(INCS) -c $^ -o $(^:.c=.o)

$(NAME):	$(OBJS) $(LIBFT)
			$(LIB)	$(NAME) $(OBJS)

$(LIBFT):
			make -C $(LIBFT_DIR)
			cp $(LIBFT) $(NAME)

clean:
			make clean -C $(LIBFT_DIR)
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
