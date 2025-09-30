# 実行ファイル名
NAME = philo

# コンパイラとフラグ
CC = cc
# -Wall -Wextra -Werror は課題の要件です。
# -pthread は、pthreadライブラリを使用したプログラムをコンパイル・リンクするために必須です。
CFLAGS = -Wall -Wextra -Werror -pthread

# ソースファイル (.c)
# ここにあなたの.c ファイルをすべて列挙してください。
# 例: SRCS = main.c init.c actions.c monitor.c utils.c
SRCS = 	main.c \
		init.c \
		error.c \
		parse.c \
		utils.c \
		simulate.c

# オブジェクトファイル (.o) - SRCSから自動的に生成されます
OBJS = $(SRCS:.c=.o)

# 削除コマンド
RM = rm -f

# --- ルール定義 ---

# デフォルトルール: プロジェクトをコンパイルします
all: $(NAME)

# オブジェクトファイルをリンクして実行ファイルを作成するルール
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

#.c ファイルを.o ファイルにコンパイルするルール
# $< は依存関係の最初のファイル (hoge.c)、$@ はターゲットファイル (hoge.o) を意味します
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# オブジェクトファイルを削除するルール
clean:
	$(RM) $(OBJS)

# オブジェクトファイルと実行ファイルを削除するルール
fclean: clean
	$(RM) $(NAME)

# 全てをクリーンにしてから再コンパイルするルール
re: fclean all

# 偽のターゲットを宣言し、同名のファイルとの衝突を防ぎます
.PHONY: all clean fclean re
