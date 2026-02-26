/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Intersects a ray with an infinite plane and returns positive t. */
int	intersect_plane(const t_ray *ray, const t_object *obj, double *t)
{
	double	denom;
	double	numer;

	denom = vec_dot(obj->plane.normal, ray->dir);
	if (fabs(denom) < EPSILON)
		return (0);
	numer = vec_dot(vec_sub(obj->plane.point, ray->origin), obj->plane.normal);
	*t = numer / denom;
	return (*t > EPSILON);
}
