/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Prints subject-compliant error header with a custom message. */
int	rt_error(const char *msg, int line_no)
{
	write(2, "Error\n", 6);
	if (line_no >= 0)
		printf("line %d: %s\n", line_no, msg);
	else
		printf("%s\n", msg);
	return (1);
}

/* Checks that the input filename ends with .rt. */
static int	has_rt_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strcmp(path + len - 3, ".rt"));
}

/* Splits loaded content by lines and parses each non-empty line. */
static int	parse_content(t_scene *scene, char *content)
{
	size_t	start;
	size_t	i;
	int		line_no;
	char	*line;

	start = 0;
	i = 0;
	line_no = 1;
	while (1)
	{
		if (content[i] == '\n' || content[i] == '\0')
		{
			line = ft_substr(content, start, i - start);
			if (!line || parse_line(scene, line, line_no))
				return (free(line), 1);
			free(line);
			if (content[i] == '\0')
				break ;
			start = ++i;
			line_no++;
		}
		else
			i++;
	}
	return (0);
}

/* Parses a complete .rt file into the scene structure. */
int	parse_scene(t_scene *scene, const char *path)
{
	char	*content;

	if (!has_rt_extension(path))
		return (rt_error("scene file extension must be .rt", -1));
	content = read_entire_file(path);
	if (!content)
		return (1);
	if (parse_content(scene, content))
		return (free(content), 1);
	free(content);
	return (0);
}
