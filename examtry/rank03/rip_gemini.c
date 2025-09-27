
#include <stdlib.h> // malloc, free を使用するために追加
#include <unistd.h>

// 関数プロトタイプ宣言
int		is_balanced(char *str);
void	print_ans(char *str);

/*
 * 文字列の長さを返す関数
 */
int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
 * 左右のカッコの数を数える関数
 */
void	count_par(char *str, int *left, int *right)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			(*left)++;
		else if (str[i] == ')')
			(*right)++;
	}
}

/*
 * 新しい再帰関数：組み合わせを生成する
 * str: 処理対象の文字列
 * index: 現在注目している文字のインデックス
 * to_remove: 削除（置換）すべき残りのカッコの数
 * target: 削除対象のカッコの種類 ('(' または ')')
 */
void	generate_solutions(char *str, int index, int to_remove, char target)
{
	// ベースケース：文字列の最後まで探索した
	if (str[index] == '\0')
	{
		// 削除すべき個数をちょうど使い切り、かつバランスが取れていれば解として出力
		if (to_remove == 0 && is_balanced(str))
		{
			print_ans(str);
		}
		return ;
	}
	// === 再帰ステップ ===
	// パターン1: index番目の文字を「そのままにする」場合
	generate_solutions(str, index + 1, to_remove, target);
	// パターン2: index番目の文字が削除対象であり、まだ削除枠が残っている場合
	// その文字を「スペースに置き換える」ことを試す
	if (str[index] == target && to_remove > 0)
	{
		str[index] = ' '; // 文字をスペースに置き換える
		generate_solutions(str, index + 1, to_remove - 1, target);
		str[index] = target; //【重要】バックトラック：文字を元に戻す
	}
}

/*
 * 文字列のカッコのバランスが取れているかチェックする関数（修正版）
 */
int	is_balanced(char *str)
{
	int	pos;

	pos = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			pos++;
		else if (str[i] == ')')
			pos--;
		// 途中で閉じカッコが開きカッコの数を上回ったらNG
		if (pos < 0)
			return (0);
	}
	// 最終的にカウンターが0でなければNG
	return (pos == 0);
}

/*
 * 解答を出力する関数
 */
void	print_ans(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
	write(1, "\n", 1); // cat -eでの表示を考慮し、スペースは削除
}

int	main(int argc, char **argv)
{
	int		right;
	int		left;
	int		len;
	char	*str_copy;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	// 元の引数を変更しないようにコピーを作成
	str_copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!str_copy)
		return (1);
	for (int i = 0; i < len; i++)
		str_copy[i] = argv[1][i];
	str_copy[len] = '\0';
	right = 0;
	left = 0;
	count_par(str_copy, &left, &right);
	if (left == right)
	{
		// 数が同じでもバランスが取れているとは限らないのでチェックする
		if (is_balanced(str_copy))
			print_ans(str_copy);
	}
	else if (left > right)
	{
		generate_solutions(str_copy, 0, left - right, '(');
	}
	else // left < right
	{
		generate_solutions(str_copy, 0, right - left, ')');
	}
	free(str_copy); // メモリを解放
	return (0);
}
