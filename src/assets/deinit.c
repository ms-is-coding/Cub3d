/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:35:52 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 15:17:21 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "assets.h"
#include "gfx/gfx.h"

static void	free_tile_textures(t_assets *a)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 96)
	{
		if (a->tiles[i].flags == TILE_F_NONE)
		{
			i++;
			continue ;
		}
		j = DIR_DEFAULT;
		while (j < DIR_COUNT)
		{
			if (a->tiles[i].textures[j])
				gfx_image_destroy(a->gfx->mlx, a->tiles[i].textures[j]);
			j++;
		}
		i++;
	}
}

static void	free_asset_textures(t_assets *a)
{
	if (a->skybox)
		gfx_image_destroy(a->gfx->mlx, a->skybox);
	if (a->invalid)
		gfx_image_destroy(a->gfx->mlx, a->invalid);
}

void	assets_deinit(t_assets *assets)
{
	if (!assets)
		return ;
	if (assets->map.data)
		free(assets->map.data);
	if (assets->gfx)
	{
		free_tile_textures(assets);
		free_asset_textures(assets);
	}
	memset(assets, 0, sizeof(t_assets));
}
