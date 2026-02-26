/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Computes the cross product between two vectors. */
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

/* Returns the euclidean length of a vector. */
double	vec_length(t_vec3 v)
{
	return (sqrt(vec_dot(v, v)));
}

/* Normalizes a vector and returns zero-vector when tiny. */
t_vec3	vec_normalize(t_vec3 v)
{
	double	len;

	len = vec_length(v);
	if (len < EPSILON)
		return (vec3(0.0, 0.0, 0.0));
	return (vec_scale(v, 1.0 / len));
}

/* Clamps a value to the inclusive [min, max] range. */
double	clamp_value(double v, double min, double max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

/* Gets a point located at ray.origin + ray.dir * t. */
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.dir, t)));
}
