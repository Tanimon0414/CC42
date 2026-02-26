/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Routes one object to its specific intersection function. */
static int	intersect_object(const t_ray *ray, const t_object *obj, double *t)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj, t));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, obj, t));
	return (intersect_cylinder(ray, obj, t));
}

/* Computes outward normal for a finite capped cylinder. */
static t_vec3	cylinder_normal(const t_object *obj, t_vec3 point)
{
	t_vec3	to_p;
	double	m;
	double	half;
	t_vec3	axis_p;

	to_p = vec_sub(point, obj->cylinder.center);
	m = vec_dot(to_p, obj->cylinder.axis);
	half = obj->cylinder.height * 0.5;
	if (fabs(m - half) <= 1e-3)
		return (obj->cylinder.axis);
	if (fabs(m + half) <= 1e-3)
		return (vec_scale(obj->cylinder.axis, -1.0));
	axis_p = vec_add(obj->cylinder.center, vec_scale(obj->cylinder.axis, m));
	return (vec_normalize(vec_sub(point, axis_p)));
}

/* Stores hit point and surface normal oriented against incoming ray. */
static void	fill_hit(t_hit *hit, const t_ray *ray,
	const t_object *obj, double t)
{
	t_vec3	normal;

	hit->hit = 1;
	hit->t = t;
	hit->point = ray_at(*ray, t);
	if (obj->type == OBJ_SPHERE)
		normal = vec_normalize(vec_sub(hit->point, obj->sphere.center));
	else if (obj->type == OBJ_PLANE)
		normal = obj->plane.normal;
	else
		normal = cylinder_normal(obj, hit->point);
	if (vec_dot(ray->dir, normal) > 0.0)
		normal = vec_scale(normal, -1.0);
	hit->normal = vec_normalize(normal);
	hit->color = obj->color;
}

/* Finds closest visible hit in front of the ray origin. */
int	hit_scene(const t_scene *scene, const t_ray *ray, t_hit *hit)
{
	int		i;
	double	t;

	hit->hit = 0;
	hit->t = INFINITY;
	i = 0;
	while (i < scene->obj_count)
	{
		if (intersect_object(ray, &scene->objects[i], &t)
			&& t > EPSILON && t < hit->t)
			fill_hit(hit, ray, &scene->objects[i], t);
		i++;
	}
	return (hit->hit);
}

/* Returns true when any object blocks the shadow ray before max_t. */
int	hit_shadow(const t_scene *scene, const t_ray *ray, double max_t)
{
	int		i;
	double	t;

	i = 0;
	while (i < scene->obj_count)
	{
		if (intersect_object(ray, &scene->objects[i], &t)
			&& t > EPSILON && t < max_t)
			return (1);
		i++;
	}
	return (0);
}
