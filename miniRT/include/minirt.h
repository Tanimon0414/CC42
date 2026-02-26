/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_object
{
	t_obj_type	type;
	t_color		color;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
	t_vec3	right;
	t_vec3	up;
	double	tan_half_fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	int			has_ambient;
	int			has_camera;
	int			has_light;
	t_object	*objects;
	int			obj_count;
	int			obj_cap;
}	t_scene;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_hit
{
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
	int		hit;
}	t_hit;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	scene;
}	t_app;

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define EPSILON 1e-6
# define SHADOW_BIAS 1e-4
# define KEY_ESC_LINUX 65307
# define KEY_ESC_MAC 53
# define PI 3.14159265358979323846

/* app */
void	init_app(t_app *app);
void	free_scene(t_scene *scene);
int		destroy_app(t_app *app, int status);
int		init_mlx(t_app *app);
void	destroy_display(void *mlx);
int		close_window(t_app *app);
int		key_press(int keycode, t_app *app);
int		expose_hook(t_app *app);
int		loop_hook(t_app *app);

/* parser */
int		parse_scene(t_scene *scene, const char *path);
char	*read_entire_file(const char *path);
char	*trim_line(const char *line);
char	**split_spaces(const char *line, int *count);
void	free_split(char **arr);
int		parse_double(const char *s, double *out);
int		parse_int(const char *s, int *out);
int		parse_ratio(const char *s, double *out);
int		parse_fov(const char *s, double *out);
int		parse_vec3(const char *s, t_vec3 *out);
int		parse_color(const char *s, t_color *out);
int		vec_is_normalized(t_vec3 v);
int		parse_line(t_scene *scene, char *line, int line_no);
int		parse_ambient(t_scene *scene, char **tk, int count, int line_no);
int		parse_camera(t_scene *scene, char **tk, int count, int line_no);
int		parse_light(t_scene *scene, char **tk, int count, int line_no);
int		parse_sphere(t_scene *scene, char **tk, int count, int line_no);
int		parse_plane(t_scene *scene, char **tk, int count, int line_no);
int		parse_cylinder(t_scene *scene, char **tk, int count, int line_no);
int		add_object(t_scene *scene, t_object obj);
int		validate_scene(const t_scene *scene);
int		rt_error(const char *msg, int line_no);

/* render */
void	build_camera_basis(t_camera *cam);
t_ray	create_camera_ray(const t_camera *cam, int x, int y);
void	render_scene(t_app *app);
int		hit_scene(const t_scene *scene, const t_ray *ray, t_hit *hit);
int		hit_shadow(const t_scene *scene, const t_ray *ray, double max_t);
int		intersect_sphere(const t_ray *ray, const t_object *obj, double *t);
int		intersect_plane(const t_ray *ray, const t_object *obj, double *t);
int		intersect_cylinder(const t_ray *ray, const t_object *obj, double *t);
t_color	shade_hit(const t_scene *scene, const t_hit *hit);
int		is_in_shadow(const t_scene *scene, const t_hit *hit);

/* strings */
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_isspace(int c);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, size_t start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/* math */
t_vec3	vec3(double x, double y, double z);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, double s);
double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
double	vec_length(t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
double	clamp_value(double v, double min, double max);
t_vec3	ray_at(t_ray ray, double t);

/* color & image */
t_color	color3(double r, double g, double b);
t_color	color_scale(t_color c, double s);
t_color	color_mul(t_color a, t_color b);
int		color_to_int(t_color c);
void	img_put_pixel(t_img *img, int x, int y, int color);

#endif
