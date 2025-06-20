# --- プロジェクト設定 ---
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- ソースファイル ---
# get_next_line のソースファイルを追加する
GNL_SRCS = get_next_line/get_next_line.c \
           get_next_line/get_next_line_utils.c

SRCS = 00_main.c \
       01_main_parser.c \
	   02_init.c \
       03_map_validator.c \
       04_path_validator.c \
       05_render.c \
       06_game.c \
       07_cleanup.c \
	   08_queue_utils.c \
       99_error.c \
       $(GNL_SRCS) # ここでGNLのソースを追加

OBJS = $(SRCS:.c=.o)

# --- ライブラリ設定 ---
# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# MiniLibX (Linux version)
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# --- コンパイラ・リンカフラグ ---
# ヘッダー検索パス
# get_next_lineのディレクトリも追加しておくとより確実
CPPFLAGS = -I. -I$(LIBFT_DIR) -I$(MLX_DIR) -Iget_next_line

# ライブラリ検索パスとリンクするライブラリ
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# --- ルール ---
.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

# Libftライブラリのビルドルール
$(LIBFT):
	@make -sC $(LIBFT_DIR)

# MiniLibXは通常ビルド済みだが、念のためルールを記述
$(MLX_LIB):
	@make -sC $(MLX_DIR)

# .cから.oを生成するルール
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@make -sC $(LIBFT_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all