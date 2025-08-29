
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// compute the distance between two points
float	distance(float a[2], float b[2])
{
	return (sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1]
				- a[1])));
}

float	cal_dis(float (*array)[2], int *cities, ssize_t size)
{
	float	dis;

	dis = 0;
	if (size <= 1)
		return (0);
	for (ssize_t i = 0; i < size - 1; i++)
		dis += distance(array[cities[i]], array[cities[i + 1]]);
	dis += distance(array[cities[0]], array[cities[size - 1]]);
	return (dis);
}

void	set_and_calc_dis(float (*array)[2], int *cities, ssize_t size,
		float *best_distance, ssize_t cur_index)
{
	int		tmp;
	float	cur_dis;

	if (cur_index == size)
	{
		cur_dis = cal_dis(array, cities, size);
		if (cur_dis < *best_distance)
			*best_distance = cur_dis;
		return ;
	}
	for (ssize_t i = cur_index; i < size; i++)
	{
		tmp = cities[i];
		cities[i] = cities[cur_index];
		cities[cur_index] = tmp;
		set_and_calc_dis(array, cities, size, best_distance, cur_index + 1);
		tmp = cities[i];
		cities[i] = cities[cur_index];
		cities[cur_index] = tmp;
	}
	return ;
}

float	tsp(float (*array)[2], ssize_t size)
{
	float	best_distance;
	int		*cities;

	if (size == 0 || size == 1)
		return (0);
	cities = malloc(sizeof(int) * size);
	if (!cities)
		return (0);
	for (int i = 0; i < size; i++)
		cities[i] = i;
	best_distance = __FLT_MAX__;
	set_and_calc_dis(array, cities, size, &best_distance, 1);
	free(cities);
	return (best_distance);
}

ssize_t	file_size(FILE *file)
{
	char	*buffer;
	size_t	n;
	ssize_t	ret;

	buffer = NULL;
	n = 0;
	errno = 0;
	for (ret = 0; getline(&buffer, &n, file) != -1; ret++)
		;
	free(buffer);
	if (errno || fseek(file, 0, SEEK_SET))
		return (-1);
	return (ret);
}

int	retrieve_file(float (*array)[2], FILE *file)
{
	int	tmp;

	for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i]
				+ 1)) != EOF; i++)
		if (tmp != 2)
		{
			errno = EINVAL;
			return (-1);
		}
	if (ferror(file))
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	char	*filename;
	FILE	*file;
	ssize_t	size;

	filename = "stdin";
	file = stdin;
	if (ac > 1)
	{
		filename = av[1];
		file = fopen(filename, "r");
	}
	if (!file)
	{
		fprintf(stderr, "Error opening %s: %m\n", filename);
		return (1);
	}
	size = file_size(file);
	if (size == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", filename);
		fclose(file);
		return (1);
	}
	float(*array)[2] = calloc(size, sizeof(float[2]));
	if (!array)
	{
		fprintf(stderr, "Error: %m\n");
		fclose(file);
		return (1);
	}
	if (retrieve_file(array, file) == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", av[1]);
		fclose(file);
		free(array);
		return (1);
	}
	if (ac > 1)
		fclose(file);
	printf("%.2f\n", tsp(array, size));
	free(array);
	return (0);
}
