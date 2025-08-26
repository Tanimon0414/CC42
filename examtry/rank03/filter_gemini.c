
#include <stdio.h>  // printf(), perror() を使用するために必要
#include <stdlib.h> // malloc(), realloc(), free() を使用するために必要
#include <string.h> // strlen() を使用するために必要
#include <unistd.h> // read() を使用するために必要

static int	my_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
	{
		return (0);
	}
	while (n-- > 0 && *s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	// ループ終了後、nが-1になっているので+1して元のnの範囲の値に戻す
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	main(int argc, char *argv[])
{
	const char		*search_str = argv[1];
	const size_t	search_len = strlen(search_str);
	char			*input_buffer;
	size_t			total_size;
	ssize_t			bytes_read;
	char			*temp_buffer;

	if (argc != 2 || argv[1][0] == '\0')
	{
		return (1);
	}
	input_buffer = NULL;
	total_size = 0;
	const size_t CHUNK_SIZE = 4096; // 一度に読み込むサイズ
	while (1)
	{
		// 読み込みのためにメモリを拡張
		temp_buffer = realloc(input_buffer, total_size + CHUNK_SIZE);
		if (temp_buffer == NULL)
		{
			perror("Error");
			// メモリ確保失敗 [cite: 3]
			free(input_buffer);
			return (1);
		}
		input_buffer = temp_buffer;
		// 標準入力(ファイルディスクリプタ 0)から読み込み [cite: 2]
		bytes_read = read(0, input_buffer + total_size, CHUNK_SIZE);
		if (bytes_read < 0)
		{
			perror("Error");
			// 読み込みエラー [cite: 3]
			free(input_buffer);
			return (1);
		}
		if (bytes_read == 0)
		{
			// ファイルの終端に到達
			break ;
		}
		total_size += bytes_read;
	}
	// --- 3. メモリ内のデータを処理し、結果を標準出力へ書き出す ---
	for (size_t i = 0; i < total_size;)
	{
		// iから始まる部分文字列が検索文字列と一致するか確認
		// (ただし、バッファの範囲を超えないようにする)
		if (i + search_len <= total_size && my_strncmp(input_buffer + i,
				search_str, search_len) == 0)
		{
			// 一致した場合、同じ長さのアスタリスクを出力 [cite: 2, 3]
			for (size_t j = 0; j < search_len; j++)
			{
				printf("*");
			}
			// インデックスを検索文字列の分だけ進める
			i += search_len;
		}
		else
		{
			// 一致しなかった場合、その1文字を出力
			printf("%c", input_buffer[i]);
			// インデックスを1つ進める
			i++;
		}
	}
	// --- 4. 後処理 ---
	free(input_buffer);
	return (0);
}
