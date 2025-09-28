/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:24:02 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 15:27:41 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_parse_uint64(const char *str, uint64_t *dest)
{
	uint64_t	result;

	result = 0;
	if (!str || str[0] == '\0')
		return (false);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (false);
	while (ft_isdigit(*str))
	{
		if (result > (UINT64_MAX - (*str - '0')) / 10)
			return (false);
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (false);
	*dest = result;
	return (true);
}

bool	set_args(t_data *data, char **av, int ac)
{
	uint64_t	temp;

	if (!ft_parse_uint64(av[1], &temp) || temp == 0 || temp > 300)
		return (false);
	data->philo_num = (int)temp;
	if (!ft_parse_uint64(av[2], &data->death_time) || data->death_time == 0)
		return (false);
	if (!ft_parse_uint64(av[3], &data->eat_time) || data->eat_time == 0)
		return (false);
	if (!ft_parse_uint64(av[4], &data->sleep_time) || data->sleep_time == 0)
		return (false);
	if (ac == 6)
	{
		if (!ft_parse_uint64(av[5], &temp) || temp == 0)
			return (false);
		data->meals_nb = (int)temp;
	}
	else
		data->meals_nb = -1;
	return (true);
}
