/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* Handles the window close action from window manager. */
int	close_window(t_app *app)
{
	destroy_app(app, 0);
	exit(0);
	return (0);
}

/* Handles key presses and exits on ESC. */
int	key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC_LINUX || keycode == KEY_ESC_MAC)
		return (close_window(app));
	return (0);
}

/* Re-displays the rendered image when expose event occurs. */
int	expose_hook(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
	return (0);
}

/* Refreshes the window image during the mlx event loop. */
int	loop_hook(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
	return (0);
}
