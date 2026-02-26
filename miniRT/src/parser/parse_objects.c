/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Appends one parsed object to the dynamic object array. */
int	add_object(t_scene *scene, t_object obj)
{
	t_object	*new_arr;
	int			new_cap;

	if (scene->obj_count == scene->obj_cap)
	{
		new_cap = scene->obj_cap;
		if (new_cap == 0)
			new_cap = 8;
		else
			new_cap *= 2;
		new_arr = (t_object *)malloc(sizeof(t_object) * new_cap);
		if (!new_arr)
			return (1);
		ft_memcpy(new_arr, scene->objects, sizeof(t_object) * scene->obj_count);
		free(scene->objects);
		scene->objects = new_arr;
		scene->obj_cap = new_cap;
	}
	scene->objects[scene->obj_count++] = obj;
	return (0);
}

/* Parses sphere: center, diameter, color. */
int	parse_sphere(t_scene *scene, char **tk, int count, int line_no)
{
	t_object	obj;
	double		diameter;

	if (count != 4)
		return (rt_error("invalid sphere format", line_no));
	if (parse_vec3(tk[1], &obj.sphere.center)
		|| parse_double(tk[2], &diameter)
		|| parse_color(tk[3], &obj.color) || diameter <= 0.0)
		return (rt_error("invalid sphere values", line_no));
	obj.type = OBJ_SPHERE;
	obj.sphere.radius = diameter * 0.5;
	if (add_object(scene, obj))
		return (rt_error("malloc failed", line_no));
	return (0);
}

/* Parses plane: point, normal vector, color. */
int	parse_plane(t_scene *scene, char **tk, int count, int line_no)
{
	t_object	obj;

	if (count != 4)
		return (rt_error("invalid plane format", line_no));
	if (parse_vec3(tk[1], &obj.plane.point)
		|| parse_vec3(tk[2], &obj.plane.normal)
		|| !vec_is_normalized(obj.plane.normal)
		|| parse_color(tk[3], &obj.color))
		return (rt_error("invalid plane values", line_no));
	obj.type = OBJ_PLANE;
	obj.plane.normal = vec_normalize(obj.plane.normal);
	if (add_object(scene, obj))
		return (rt_error("malloc failed", line_no));
	return (0);
}

/* Parses cylinder: center, axis, diameter, height, color. */
int	parse_cylinder(t_scene *scene, char **tk, int count, int line_no)
{
	t_object	obj;
	double		diameter;
	double		height;

	if (count != 6)
		return (rt_error("invalid cylinder format", line_no));
	if (parse_vec3(tk[1], &obj.cylinder.center)
		|| parse_vec3(tk[2], &obj.cylinder.axis)
		|| !vec_is_normalized(obj.cylinder.axis)
		|| parse_double(tk[3], &diameter)
		|| parse_double(tk[4], &height)
		|| parse_color(tk[5], &obj.color) || diameter <= 0.0 || height <= 0.0)
		return (rt_error("invalid cylinder values", line_no));
	obj.type = OBJ_CYLINDER;
	obj.cylinder.axis = vec_normalize(obj.cylinder.axis);
	obj.cylinder.radius = diameter * 0.5;
	obj.cylinder.height = height;
	if (add_object(scene, obj))
		return (rt_error("malloc failed", line_no));
	return (0);
}

/* Verifies required mandatory elements exist exactly once. */
int	validate_scene(const t_scene *scene)
{
	if (!scene->has_ambient)
		return (rt_error("missing ambient light", -1));
	if (!scene->has_camera)
		return (rt_error("missing camera", -1));
	if (!scene->has_light)
		return (rt_error("missing light", -1));
	if (scene->obj_count == 0)
		return (rt_error("missing objects", -1));
	return (0);
}
