/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Splits a comma-separated token into exactly three parts. */
static int	split_three(const char *s, char **a, char **b, char **c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] && s[i] != ',')
		i++;
	if (!s[i])
		return (1);
	j = i + 1;
	while (s[j] && s[j] != ',')
		j++;
	if (!s[j])
		return (1);
	*a = ft_substr(s, 0, i);
	*b = ft_substr(s, i + 1, j - i - 1);
	*c = ft_strdup(s + j + 1);
	if (!*a || !*b || !*c)
		return (free(*a), free(*b), free(*c), 1);
	return (0);
}

/* Parses x,y,z as doubles. */
int	parse_vec3(const char *s, t_vec3 *out)
{
	char	*a;
	char	*b;
	char	*c;
	int		err;

	a = NULL;
	b = NULL;
	c = NULL;
	if (split_three(s, &a, &b, &c))
		return (1);
	err = parse_double(a, &out->x) || parse_double(b, &out->y)
		|| parse_double(c, &out->z);
	free(a);
	free(b);
	free(c);
	return (err);
}

/* Parses R,G,B as ints in [0, 255]. */
int	parse_color(const char *s, t_color *out)
{
	t_vec3	rgb;

	if (parse_vec3(s, &rgb))
		return (1);
	if (rgb.x < 0.0 || rgb.x > 255.0 || rgb.y < 0.0 || rgb.y > 255.0)
		return (1);
	if (rgb.z < 0.0 || rgb.z > 255.0)
		return (1);
	if (rgb.x != floor(rgb.x) || rgb.y != floor(rgb.y)
		|| rgb.z != floor(rgb.z))
		return (1);
	*out = color3(rgb.x, rgb.y, rgb.z);
	return (0);
}

/* Checks if a vector is normalized and each component is in [-1, 1]. */
int	vec_is_normalized(t_vec3 v)
{
	double	len;

	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0
		|| v.z < -1.0 || v.z > 1.0)
		return (0);
	len = vec_length(v);
	return (fabs(len - 1.0) <= 1e-3);
}

/* Parses a ratio in the inclusive [0.0, 1.0] interval. */
int	parse_ratio(const char *s, double *out)
{
	if (parse_double(s, out))
		return (1);
	if (*out < 0.0 || *out > 1.0)
		return (1);
	return (0);
}
