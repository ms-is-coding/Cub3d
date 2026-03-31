/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:43 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 14:54:48 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/error.h"

#include "parser_internal.h"

static int	validate_asset_textures(t_assets *a)
{
	if (!a->asset_tex[TEX_INVALID])
		return (print_error(MOD_PARSER, ERR_TEX_NO_INVALID, 1));
	return (0);
}

static int	no_valid_textures(t_assets *a, size_t pos)
{
	a->tiles[pos].textures[DIR_INVALID] = a->asset_tex[TEX_INVALID];
	if (a->tiles[pos].flags & TILE_F_RAY_BLOCK
		&& !a->tiles[pos].textures[DIR_DEFAULT]
		&& (!a->tiles[pos].textures[DIR_NORTH]
			|| !a->tiles[pos].textures[DIR_SOUTH]
			|| !a->tiles[pos].textures[DIR_WEST]
			|| !a->tiles[pos].textures[DIR_EAST]))
		return (print_warning(MOD_PARSER, WARN_TEX_NO_DIR, 1));
	return (0);
}

static int	validate_tile_textures(t_assets *a)
{
	size_t		i;

	i = 0;
	while (i < 96)
	{
		if (a->tiles[i].flags == TILE_F_NONE)
		{
			i++;
			continue ;
		}
		no_valid_textures(a, i);
		i++;
	}
	return (0);
}

int	validate_textures(t_assets *a)
{
	if (validate_asset_textures(a))
		return (1);
	if (validate_tile_textures(a))
		return (1);
	return (0);
}
