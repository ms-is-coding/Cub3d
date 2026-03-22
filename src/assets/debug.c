/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 15:37:15 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 19:07:03 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets.h"

#ifdef DEBUG

# include <stddef.h>
# include <stdio.h>

static void	debug_print_id_and_flags(char id, t_tile_flags flags)
{
	dprintf(2, "\n- Tile '%c':", id);
	if (flags == TILE_F_NONE)
	{
		dprintf(2, " NONE\n");
		return ;
	}
	if (flags & TILE_F_VOID)
		dprintf(2, " VOID");
	if (flags & TILE_F_SOLID)
		dprintf(2, " SOLID");
	if (flags & TILE_F_WALKABLE)
		dprintf(2, " WALKABLE");
	if (flags & TILE_F_RAY_BLOCK)
		dprintf(2, " RAY_BLOCK");
	if (flags & TILE_F_DOOR)
		dprintf(2, " DOOR");
	if (flags & TILE_F_PLAYER)
		dprintf(2, " PLAYER");
	dprintf(2, "\n");
}

static void	debug_print_tile(const t_tile *tile, char id)
{
	debug_print_id_and_flags(id, tile->flags);
	if (tile->textures[DIR_DEFAULT])
		dprintf(2, "~ Base texture defined\n");
	if (tile->textures[DIR_NORTH])
		dprintf(2, "~ North texture defined\n");
	if (tile->textures[DIR_SOUTH])
		dprintf(2, "~ South texture defined\n");
	if (tile->textures[DIR_WEST])
		dprintf(2, "~ West texture defined\n");
	if (tile->textures[DIR_EAST])
		dprintf(2, "~ East texture defined\n");
	if (tile->colors[DIR_DEFAULT] != RGB_INVALID)
		dprintf(2, "~ Base color defined: 0x%06X\n", tile->colors[DIR_DEFAULT]);
	if (tile->colors[DIR_NORTH] != RGB_INVALID)
		dprintf(2, "~ North color defined: 0x%06X\n", tile->colors[DIR_NORTH]);
	if (tile->colors[DIR_SOUTH] != RGB_INVALID)
		dprintf(2, "~ South color defined: 0x%06X\n", tile->colors[DIR_SOUTH]);
	if (tile->colors[DIR_WEST] != RGB_INVALID)
		dprintf(2, "~ West color defined: 0x%06X\n", tile->colors[DIR_WEST]);
	if (tile->colors[DIR_EAST] != RGB_INVALID)
		dprintf(2, "~ East color defined: 0x%06X\n", tile->colors[DIR_EAST]);
}

static void	debug_print_map(const t_map *map)
{
	size_t	x;
	size_t	y;

	dprintf(2, "\n- Size: %zu * %zu\n\n", map->width, map->height);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
			dprintf(2, "%c", map->data[y * map->width + x++] + 32);
		dprintf(2, "\n");
		y++;
	}
}

void	debug_print_assets(t_assets *a)
{
	size_t	i;

	dprintf(2, "\t\t- ASSETS -\n");
	dprintf(2, "\nTiles:\n");
	i = 0;
	while (i < 96)
	{
		if (a->tiles[i].flags != TILE_F_NONE)
			debug_print_tile(&a->tiles[i], (char)(i + 32));
		i++;
	}
	dprintf(2, "\nMap:\n");
	debug_print_map(&a->map);
	dprintf(2, "\nOther:\n");
	if (a->skybox)
		dprintf(2, "\t-Skybox texture defined\n");
	if (a->invalid)
		dprintf(2, "\t-Invalid texture defined\n");
	if (a->floor != RGB_INVALID)
		dprintf(2, "\t-Floor color defined: 0x%06X\n", a->floor);
	if (a->ceiling != RGB_INVALID)
		dprintf(2, "\t-Ceiling color defined: 0x%06X\n", a->ceiling);
	dprintf(2, "\n");
}

#else

void	debug_print_assets(t_assets *a)
{
	(void)a;
	return ;
}

#endif
