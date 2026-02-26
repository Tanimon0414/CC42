/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* Entry point: parse scene, render once and run mlx loop. */
int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (rt_error("usage: ./miniRT <scene.rt>", -1));
	init_app(&app);
	if (parse_scene(&app.scene, argv[1]))
		return (destroy_app(&app, 1));
	if (validate_scene(&app.scene))
		return (destroy_app(&app, 1));
	if (init_mlx(&app))
		return (destroy_app(&app, 1));
	render_scene(&app);
	mlx_expose_hook(app.win, expose_hook, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	mlx_hook(app.win, 2, 1L << 0, key_press, &app);
	mlx_hook(app.win, 17, 0, close_window, &app);
	mlx_loop(app.mlx);
	return (destroy_app(&app, 0));
}
