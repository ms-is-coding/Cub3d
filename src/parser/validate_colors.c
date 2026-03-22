/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:34 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:31:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "utils/error.h"

#include "parser_internal.h"

static int	validate_asset_colors(t_assets *a)
{
	if (a->ceiling == RGB_INVALID)
		print_warning(MOD_PARSER, WARN_COL_NO_CEILING, 0);
	if (a->floor == RGB_INVALID)
		print_warning(MOD_PARSER, WARN_COL_NO_FLOOR, 0);
	return (0);
}

static int	no_valid_colors_and_textures(t_assets *a, size_t pos)
{
	if (a->tiles[pos].flags & TILE_F_RAY_BLOCK
		&& !a->tiles[pos].textures[DIR_DEFAULT]
		&& a->tiles[pos].colors[DIR_DEFAULT] == RGB_INVALID
		&& ((!a->tiles[pos].textures[DIR_NORTH]
				&& a->tiles[pos].colors[DIR_NORTH] == RGB_INVALID)
			|| (!a->tiles[pos].textures[DIR_SOUTH]
				&& a->tiles[pos].colors[DIR_SOUTH] == RGB_INVALID)
			|| (!a->tiles[pos].textures[DIR_EAST]
				&& a->tiles[pos].colors[DIR_EAST] == RGB_INVALID)
			|| (!a->tiles[pos].textures[DIR_WEST]
				&& a->tiles[pos].colors[DIR_WEST] == RGB_INVALID)))
		return (print_warning(MOD_PARSER, WARN_COL_NO_DIR, 0));
	return (0);
}

static int	validate_tile_colors(t_assets *a)
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
		no_valid_colors_and_textures(a, i);
		i++;
	}
	return (0);
}

int	validate_colors(t_assets *a)
{
	validate_asset_colors(a);
	validate_tile_colors(a);
	return (0);
}
