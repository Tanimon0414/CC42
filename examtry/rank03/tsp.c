
#include <stdio.h>
#include <stdlib.h>

// 都市の座標を格納する構造体
typedef struct
{
	float	x;
	float	y;
}			City;

int	main(void)
{
	City *cities = NULL; // 都市の配列を指すポインタ
	int city_count = 0;  // 読み込んだ都市の数
	int capacity = 0;    // 配列の現在の容量
	float x, y;
	// 標準入力が終わるまで、"%f, %f\n" の形式で読み込みを試みる [cite: 4]
	while (fscanf(stdin, "%f, %f\n", &x, &y) == 2)
	{
		// 配列の容量が足りなくなったら、メモリを拡張する
		if (city_count >= capacity)
		{
			if (capacity == 0)
				capacity = 8;
			else
				capacity = capacity * 2;
			cities = (City *)realloc(cities, capacity * sizeof(City));
			if (cities == NULL)
			{
				fprintf(stderr, "Memory allocation failed\n");
				return (1); // メモリ確保に失敗したら異常終了
			}
		}
		// 読み込んだ座標を配列に格納する
		cities[city_count].x = x;
		cities[city_count].y = y;
		city_count++;
	}
	// この時点で、'cities' 配列にすべての都市データが格納され、
	// 'city_count' に都市の総数が入っています。
	printf("Total cities read: %d\n", city_count);
	for (int i = 0; i < city_count; i++)
	{
		printf("City %d: (%f, %f)\n", i, cities[i].x, cities[i].y);
	}
	free(cities);
	return (0);
}
