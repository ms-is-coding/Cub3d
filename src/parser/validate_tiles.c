/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:45 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/21 18:29:03 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "assets/assets.h"
#include "utils/error.h"

#include "parser_internal.h"

__attribute__((unused))
static bool	has_no_conflicts(t_tile tile)
{
	(void)tile;
	return (true);
}

int	validate_tiles(t_assets *a)
{
	uint32_t	flags;
	size_t		i;

	flags = 0;
	i = 0;
	while (i < 96)
	{
		if (a->tiles[i].flags != TILE_F_NONE)
		{
			if (a->tiles[i].flags & TILE_F_WALL)
				flags |= TILE_F_WALL;
			if (a->tiles[i].flags & TILE_F_PLAYER)
				flags |= TILE_F_PLAYER;
		}
		i++;
	}
	if (!(flags & TILE_F_WALL))
		return (print_error(MOD_PARSER, ERR_TILE_NO_WALL, 1));
	if (!(flags & TILE_F_PLAYER))
		return (print_error(MOD_PARSER, ERR_TILE_NO_PLAYER, 1));
	return (0);
}
