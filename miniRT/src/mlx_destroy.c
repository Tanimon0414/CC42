/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atanimot0414 <atanimot0414@student.42.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 00:00:00 by atanimot0414      #+#    #+#             */
/*   Updated: 2026/02/26 00:00:00 by atanimot0414     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

#ifdef __linux__
/* Releases mlx display internals and the mlx context on linux. */
void	destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
}
#else

/* Keeps API symmetry on non-linux builds. */
void	destroy_display(void *mlx)
{
	(void)mlx;
}
#endif
