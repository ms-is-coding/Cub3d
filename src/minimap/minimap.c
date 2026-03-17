/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:20:10 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/16 19:51:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

#include "engine/engine.h"
#include "assets/assets.h"
#include "gfx/gfx.h"

#include "minimap.h"

void	draw_minimap(t_engine *engine)
{
	t_map	*map;
	uint8_t	flags;
	size_t	x;
	size_t	y;

	y = 0;
	map = &engine->assets.map;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			flags = map_tile_at(&engine->assets, x, y)->flags;
			if (flags & TILE_F_WALL)
				set_pixel(x, y, 0x000000, NULL);
			else if (flags & TILE_F_WALKABLE)
				set_pixel(x, y, 0xFFFFFF, NULL);
			else
				set_pixel(x, y, 0xFF0000, NULL);
			x++;
		}
		y++;
	}
}
