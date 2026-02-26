/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot <atanimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:46:18 by atanimot          #+#    #+#             */
/*   Updated: 2025/09/28 16:46:50 by atanimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Print error, release allocated resources, and return failure code. */
int	cleanup_and_exit(t_data *data, const char *error_msg)
{
	if (error_msg)
		printf("%s\n", error_msg);
	cleanup(data);
	return (1);
}
