/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Parses mandatory ambient element A. */
int	parse_ambient(t_scene *scene, char **tk, int count, int line_no)
{
	if (count != 3)
		return (rt_error("invalid ambient format", line_no));
	if (scene->has_ambient)
		return (rt_error("ambient declared more than once", line_no));
	if (parse_ratio(tk[1], &scene->ambient.ratio)
		|| parse_color(tk[2], &scene->ambient.color))
		return (rt_error("invalid ambient values", line_no));
	scene->has_ambient = 1;
	return (0);
}

/* Parses mandatory camera element C. */
int	parse_camera(t_scene *scene, char **tk, int count, int line_no)
{
	if (count != 4)
		return (rt_error("invalid camera format", line_no));
	if (scene->has_camera)
		return (rt_error("camera declared more than once", line_no));
	if (parse_vec3(tk[1], &scene->camera.pos)
		|| parse_vec3(tk[2], &scene->camera.dir)
		|| !vec_is_normalized(scene->camera.dir)
		|| parse_fov(tk[3], &scene->camera.fov))
		return (rt_error("invalid camera values", line_no));
	scene->has_camera = 1;
	return (0);
}

/* Parses mandatory light element L. */
int	parse_light(t_scene *scene, char **tk, int count, int line_no)
{
	if (count != 4)
		return (rt_error("invalid light format", line_no));
	if (scene->has_light)
		return (rt_error("light declared more than once", line_no));
	if (parse_vec3(tk[1], &scene->light.pos)
		|| parse_ratio(tk[2], &scene->light.ratio)
		|| parse_color(tk[3], &scene->light.color))
		return (rt_error("invalid light values", line_no));
	scene->has_light = 1;
	return (0);
}

/* Dispatches one non-empty line to the corresponding parser. */
int	parse_line(t_scene *scene, char *line, int line_no)
{
	char	**tk;
	int		count;

	tk = split_spaces(line, &count);
	if (!tk)
		return (rt_error("malloc failed", line_no));
	if (count == 0)
		return (free_split(tk), 0);
	if (!ft_strcmp(tk[0], "A"))
		count = parse_ambient(scene, tk, count, line_no);
	else if (!ft_strcmp(tk[0], "C"))
		count = parse_camera(scene, tk, count, line_no);
	else if (!ft_strcmp(tk[0], "L"))
		count = parse_light(scene, tk, count, line_no);
	else if (!ft_strcmp(tk[0], "sp"))
		count = parse_sphere(scene, tk, count, line_no);
	else if (!ft_strcmp(tk[0], "pl"))
		count = parse_plane(scene, tk, count, line_no);
	else if (!ft_strcmp(tk[0], "cy"))
		count = parse_cylinder(scene, tk, count, line_no);
	else
		count = rt_error("unknown identifier", line_no);
	free_split(tk);
	return (count);
}
