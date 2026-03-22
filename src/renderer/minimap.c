/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:20:56 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 18:00:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>

#include "assets/assets.h"
#include "gfx/gfx.h"
#include "utils/vectors.h"
#include "world/world.h"
#include "renderer_internal.h"

#define MM_SIZE		128
#define MM_RADIUS	2.5f
#define MM_OFFSET	10
#define MM_WALL		0x00FFFFFF
#define MM_FLOOR	0x00333333
#define MM_PLAYER	0x00FF0000
#define MM_OOB		0x00111111

static uint32_t	get_tile_color(const t_map *map, const t_tile *tiles,
					int32_t tx, int32_t ty)
{
	uint32_t	tile_id;

	if (tx < 0 || tx >= (int32_t)map->width
		|| ty < 0 || ty >= (int32_t)map->height)
		return (MM_OOB);
	tile_id = map->data[(uint32_t)ty * map->width + (uint32_t)tx];
	if (tiles[tile_id].flags & TILE_F_RAY_BLOCK)
		return (MM_WALL);
	return (MM_FLOOR);
}

static void	draw_player_dot(t_image *frame, uint32_t cx, uint32_t cy)
{
	int	dx;
	int	dy;

	dy = -4;
	while (dy <= 4)
	{
		dx = -4;
		while (dx <= 4)
		{
			if (dx * dx + dy * dy <= 16)
				set_pixel(cx + (uint32_t)dx,
					cy + (uint32_t)dy,
					MM_PLAYER,
					frame);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_image *f, const t_world *w, const t_assets *a)
{
	t_vec2u	p;
	t_vec2f	world_pos;

	p.y = 0;
	while (p.y < MM_SIZE)
	{
		p.x = 0;
		while (p.x < MM_SIZE)
		{
			world_pos.x = floorf(w->player.pos.x
					+ ((float)p.x / MM_SIZE - 0.5f) * (MM_RADIUS * 2.0f));
			world_pos.y = floorf(w->player.pos.y
					+ ((float)p.y / MM_SIZE - 0.5f) * (MM_RADIUS * 2.0f));
			set_pixel(MM_OFFSET + p.x, MM_OFFSET + p.y,
				get_tile_color(&a->map, a->tiles,
					(int32_t)world_pos.x, (int32_t)world_pos.y),
				f);
			p.x++;
		}
		p.y++;
	}
	draw_player_dot(f, MM_OFFSET + MM_SIZE / 2,
		MM_OFFSET + MM_SIZE / 2);
}
