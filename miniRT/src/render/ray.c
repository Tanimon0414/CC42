/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Builds orthonormal camera basis vectors from camera direction. */
void	build_camera_basis(t_camera *cam)
{
	t_vec3	world_up;
	double	fov;

	cam->dir = vec_normalize(cam->dir);
	world_up = vec3(0.0, 1.0, 0.0);
	if (fabs(vec_dot(cam->dir, world_up)) > 0.999)
		world_up = vec3(0.0, 0.0, 1.0);
	cam->right = vec_normalize(vec_cross(cam->dir, world_up));
	cam->up = vec_normalize(vec_cross(cam->right, cam->dir));
	fov = clamp_value(cam->fov, 0.001, 179.999);
	cam->tan_half_fov = tan((fov * PI / 180.0) * 0.5);
}

/* Creates one primary ray going through pixel center. */
t_ray	create_camera_ray(const t_camera *cam, int x, int y)
{
	t_ray	ray;
	double	nx;
	double	ny;
	double	aspect;

	nx = ((x + 0.5) / (double)WIN_WIDTH) * 2.0 - 1.0;
	ny = 1.0 - ((y + 0.5) / (double)WIN_HEIGHT) * 2.0;
	aspect = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	ray.origin = cam->pos;
	ray.dir = vec_add(cam->dir,
			vec_scale(cam->right, nx * cam->tan_half_fov));
	ray.dir = vec_add(ray.dir,
			vec_scale(cam->up, ny * cam->tan_half_fov / aspect));
	ray.dir = vec_normalize(ray.dir);
	return (ray);
}
