
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	str1[4];
	char	str2[4];

	printf("文字列を入力してEnterボタンを押してください\n");
	scanf("ID:%s", str1);
	printf("入力された文字列は：%s\n", str1);
	printf("文字列を入力してEnterボタンを押してください\n");
	scanf("%s", str2);
	printf("入力された文字列は：%s\n", str2);
	return (0);
}
