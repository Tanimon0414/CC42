NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Iminilibx-linux
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

SRCS = src/main.c \
	src/app.c \
	src/mlx_destroy.c \
	src/hooks.c \
	src/parser/read_file.c \
	src/parser/parse_scene.c \
	src/parser/parse_tokens.c \
	src/parser/parse_numbers.c \
	src/parser/parse_values.c \
	src/parser/parse_values2.c \
	src/parser/parse_elements.c \
	src/parser/parse_objects.c \
	src/render/render.c \
	src/render/ray.c \
	src/render/intersect.c \
	src/render/intersect_sphere.c \
	src/render/intersect_plane.c \
	src/render/intersect_cylinder.c \
	src/render/shading.c \
	src/utils/string.c \
	src/utils/string2.c \
	src/utils/vector.c \
	src/utils/vector2.c \
	src/utils/color.c

OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c include/minirt.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
