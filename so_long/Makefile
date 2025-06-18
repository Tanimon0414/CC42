NAME = so_long
CC = cc

# -Iでlibftとminilibxの両方のヘッダパスを指定する
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(LIBFT_DIR)

# --- リンカフラグ ---
# -Lでライブラリのパスを、-lでライブラリ名を指定する
# libftとminilibxの両方をリンク対象にする
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft

# Cソースファイル（ご自身のファイル名に合わせてください）
SRCS = so_long.c get_next_line.c main.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# デフォルトルール
all: $(NAME)

# 実行ファイルを生成するルール
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# .cファイルから.oファイルを生成するルール
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# オブジェクトファイルを削除するルール
clean:
	rm -f $(OBJS)

# 実行ファイルとオブジェクトファイルをすべて削除するルール
fclean: clean
	rm -f $(NAME)

# 再コンパイル用のルール
re: fclean all

# .PHONYでこれらのターゲットがファイル名と競合しないようにします
.PHONY: all clean fclean re