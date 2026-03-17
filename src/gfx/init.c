/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/17 11:27:15 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "gfx.h"
#include <stdio.h>

int	gfx_init(t_gfx *gfx, const t_options *opt)
{
	gfx->mlx = mlx_init();
	if (!gfx->mlx)
	{
		// todo: print error
		return (1);
	}
	printf("%ux%u\n", opt->width, opt->height);
	gfx->win = mlx_new_window(
		gfx->mlx,
		(int)opt->width,
		(int)opt->height,
		(char *)(intptr_t)"Cub3D"
		);
	if (!gfx->win)
	{
		// todo: print error
		return (1);
	}
	return (0);
}
