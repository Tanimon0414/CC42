/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Fills every screen pixel by tracing one primary ray. */
static void	render_pixels(t_app *app)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	t_color	c;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = create_camera_ray(&app->scene.camera, x, y);
			if (hit_scene(&app->scene, &ray, &hit))
				c = shade_hit(&app->scene, &hit);
			else
				c = color3(0.0, 0.0, 0.0);
			img_put_pixel(&app->img, x, y, color_to_int(c));
			x++;
		}
		y++;
	}
}

/* Builds camera basis, renders scene once and displays image. */
void	render_scene(t_app *app)
{
	build_camera_basis(&app->scene.camera);
	render_pixels(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
}
