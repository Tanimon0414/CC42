/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Adds two colors channel-wise. */
static t_color	add_color(t_color a, t_color b)
{
	return (color3(a.r + b.r, a.g + b.g, a.b + b.b));
}

/* Computes ambient lighting term for one hit point. */
static t_color	ambient_term(const t_scene *scene, const t_hit *hit)
{
	t_color	ambient_tint;
	t_color	base;

	ambient_tint = color_scale(scene->ambient.color, 1.0 / 255.0);
	base = color_mul(hit->color, ambient_tint);
	return (color_scale(base, scene->ambient.ratio));
}

/* Casts one shadow ray toward the light and checks any blocker. */
int	is_in_shadow(const t_scene *scene, const t_hit *hit)
{
	t_ray	shadow;
	t_vec3	to_light;
	double	dist;

	to_light = vec_sub(scene->light.pos, hit->point);
	dist = vec_length(to_light);
	shadow.origin = vec_add(hit->point, vec_scale(hit->normal, SHADOW_BIAS));
	shadow.dir = vec_normalize(to_light);
	return (hit_shadow(scene, &shadow, dist - SHADOW_BIAS));
}

/* Computes final shaded color using ambient + diffuse + hard shadow. */
t_color	shade_hit(const t_scene *scene, const t_hit *hit)
{
	t_color	out;
	t_color	diffuse;
	t_vec3	light_dir;
	double	n_dot_l;

	out = ambient_term(scene, hit);
	if (is_in_shadow(scene, hit))
		return (out);
	light_dir = vec_normalize(vec_sub(scene->light.pos, hit->point));
	n_dot_l = fmax(0.0, vec_dot(hit->normal, light_dir));
	diffuse = color_mul(hit->color,
			color_scale(scene->light.color, 1.0 / 255.0));
	diffuse = color_scale(diffuse, scene->light.ratio * n_dot_l);
	return (add_color(out, diffuse));
}
