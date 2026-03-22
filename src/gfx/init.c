/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/22 15:28:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "mlx.h"
#include "gfx.h"
#include "utils/error.h"

int	gfx_init(t_gfx *gfx, const t_options *opt)
{
	if (!gfx || !opt)
		return (print_error(MOD_GFX, ERR_NULL_PTR, 1));
	gfx->mlx = mlx_init();
	if (!gfx->mlx)
		return (print_error(MOD_GFX, ERR_MLX, 1));
	gfx->win = mlx_new_window(
			gfx->mlx,
			(int)opt->width,
			(int)opt->height,
			(char *)(intptr_t)"Cub3D"
			);
	if (!gfx->win)
	{
		gfx_deinit(gfx);
		return (print_error(MOD_GFX, ERR_WIN, 1));
	}
	return (0);
}
