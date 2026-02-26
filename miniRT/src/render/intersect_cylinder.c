/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Checks if side intersection lies within finite cylinder height. */
static int	within_height(const t_ray *ray, t_cylinder cy, t_vec3 oc, double t)
{
	double	m;

	m = vec_dot(oc, cy.axis) + t * vec_dot(ray->dir, cy.axis);
	return (fabs(m) <= cy.height * 0.5);
}

/* Tests the cylinder side surface and returns nearest valid t. */
static int	hit_side(const t_ray *ray, t_cylinder cy, double *t)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	o_perp;
	double	abc[3];
	double	root[2];

	oc = vec_sub(ray->origin, cy.center);
	d_perp = vec_sub(ray->dir, vec_scale(cy.axis, vec_dot(ray->dir, cy.axis)));
	o_perp = vec_sub(oc, vec_scale(cy.axis, vec_dot(oc, cy.axis)));
	abc[0] = vec_dot(d_perp, d_perp);
	abc[1] = 2.0 * vec_dot(d_perp, o_perp);
	abc[2] = vec_dot(o_perp, o_perp) - cy.radius * cy.radius;
	if (abc[0] < EPSILON || abc[1] * abc[1] - 4.0 * abc[0] * abc[2] < 0.0)
		return (0);
	root[0] = (-abc[1] - sqrt(abc[1] * abc[1] - 4.0 * abc[0] * abc[2]))
		/ (2.0 * abc[0]);
	root[1] = (-abc[1] + sqrt(abc[1] * abc[1] - 4.0 * abc[0] * abc[2]))
		/ (2.0 * abc[0]);
	if (root[0] > EPSILON && within_height(ray, cy, oc, root[0]))
		return (*t = root[0], 1);
	if (root[1] > EPSILON && within_height(ray, cy, oc, root[1]))
		return (*t = root[1], 1);
	return (0);
}

/* Tests one circular cap and returns t or -1 when there is no hit. */
static double	hit_cap(const t_ray *ray, t_vec3 center,
	t_vec3 normal, double r)
{
	t_vec3	p;
	double	denom;
	double	t;

	denom = vec_dot(ray->dir, normal);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vec_dot(vec_sub(center, ray->origin), normal) / denom;
	if (t <= EPSILON)
		return (-1.0);
	p = vec_sub(ray_at(*ray, t), center);
	if (vec_dot(p, p) > r * r + EPSILON)
		return (-1.0);
	return (t);
}

/* Tests both caps and keeps nearest t when any cap is hit. */
static int	hit_caps(const t_ray *ray, t_cylinder cy, double *t)
{
	t_vec3	center;
	t_vec3	normal;
	double	top_t;
	double	bot_t;

	center = vec_add(cy.center, vec_scale(cy.axis, cy.height * 0.5));
	normal = cy.axis;
	top_t = hit_cap(ray, center, normal, cy.radius);
	center = vec_sub(cy.center, vec_scale(cy.axis, cy.height * 0.5));
	normal = vec_scale(cy.axis, -1.0);
	bot_t = hit_cap(ray, center, normal, cy.radius);
	if (top_t > 0.0 && bot_t > 0.0)
		*t = fmin(top_t, bot_t);
	else if (top_t > 0.0)
		*t = top_t;
	else if (bot_t > 0.0)
		*t = bot_t;
	else
		return (0);
	return (1);
}

/* Returns nearest intersection t for finite capped cylinder. */
int	intersect_cylinder(const t_ray *ray, const t_object *obj, double *t)
{
	double	t_side;
	double	t_caps;
	int		has_side;
	int		has_caps;

	has_side = hit_side(ray, obj->cylinder, &t_side);
	has_caps = hit_caps(ray, obj->cylinder, &t_caps);
	if (has_side && has_caps)
		*t = fmin(t_side, t_caps);
	else if (has_side)
		*t = t_side;
	else if (has_caps)
		*t = t_caps;
	else
		return (0);
	return (1);
}
