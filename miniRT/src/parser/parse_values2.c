/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Parses FOV degrees in the inclusive [0, 180] interval. */
int	parse_fov(const char *s, double *out)
{
	if (parse_double(s, out))
		return (1);
	if (*out < 0.0 || *out > 180.0)
		return (1);
	return (0);
}
