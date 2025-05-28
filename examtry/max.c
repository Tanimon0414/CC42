
int	max(int *tab, unsigned int len)
{
	int	i;
	int	max;

	i = 0;
	if (len == 0)
		return (0);
	max = tab[0];
	while (i < len)
	{
		if (tab[i] > max)
			max = tab[i];
		i++;
	}
	return (max);
}
