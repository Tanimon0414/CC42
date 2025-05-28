# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kishigam <kishigam@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 00:28:10 by kishigam          #+#    #+#              #
#    Updated: 2022/08/29 23:59:54 by kishigam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

NAME_SERVER = server
NAME_CLIENT = client

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS = server.c client.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(NAME_CLIENT) $(NAME_SERVER)

bonus: server client

$(NAME_SERVER): server.o $(LIBFT)
	$(CC) -o $@ $< -LLibft -lft

$(NAME_CLIENT): client.o $(LIBFT)
	$(CC) -o $@ $< -LLibft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

$(LIBFT):
	make -C Libft

clean:
	rm -f $(OBJS)
	make -C Libft clean
	
fclean: clean
	rm -f server client Libft/Libft.a

re: fclean all

.PHONY: $(NAME) all bonus Libft clean fclean re
