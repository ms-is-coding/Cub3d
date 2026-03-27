/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:20:56 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/28 00:26:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <math.h>

#include "assets/assets.h"
#include "gfx/gfx.h"
#include "utils/vectors.h"
#include "world/world.h"
#include "renderer_internal.h"

#define MM_SIZE		256
#define MM_SCALE	25
#define MM_WALL		0x00FFFFFF
#define MM_DOOR		0x00FFFF00
#define MM_FLOOR	0x00333333
#define MM_OOB		0x00111111
#define MM_BORDER	0x00FF0000

static uint32_t	get_tile_color(const t_map *map, const t_tile *tiles,
					int32_t tx, int32_t ty)
{
	uint32_t	tile_id;

	if (tx < 0 || tx >= (int32_t)map->width
		|| ty < 0 || ty >= (int32_t)map->height)
		return (MM_OOB);
	tile_id = map->data[(uint32_t)ty * map->width + (uint32_t)tx];
	if (tiles[tile_id].flags & TILE_F_ENTITY)
		return (MM_DOOR);
	else if (tiles[tile_id].flags & TILE_F_VOID)
		return (MM_OOB);
	else if (tiles[tile_id].flags & TILE_F_SOLID)
		return (MM_WALL);
	return (MM_FLOOR);
}

static inline bool	in_fov(int32_t dx, int32_t dy, int32_t r, float half_fov)
{
	return ((dx * dx + dy * dy <= r * r)
		&& fabsf(atan2f((float)dx, -(float)dy)) <= half_fov);
}

static void	draw_border_line(t_image *f, uint32_t cx, uint32_t cy, float angle)
{
	int32_t	i;

	i = 0;
	while (i++ < MM_SIZE / 2)
		set_pixel((uint32_t)((int32_t)cx + (int32_t)((float)i * cosf(angle))),
			(uint32_t)((int32_t)cy + (int32_t)((float)i * sinf(angle))),
			MM_BORDER, f);
}

static void	draw_border_arc(t_image *f, uint32_t cx, uint32_t cy, float half_fov)
{
	const int32_t	r = MM_SIZE / 2 - 1;
	float			angle;
	int32_t			dr;
	float			rf;

	dr = -2;
	while (++dr <= 1)
	{
		rf = (float)(r + dr);
		angle = -M_PI_2f - half_fov;
		while (angle < -M_PI_2f + half_fov)
		{
			set_pixel((uint32_t)((int32_t)cx + (int32_t)(rf * cosf(angle))),
				(uint32_t)((int32_t)cy + (int32_t)(rf * sinf(angle))),
				MM_BORDER, f);
			angle += 1.0f / rf;
		}
	}
}

static void	draw_border(t_image *f, uint32_t cx, uint32_t cy, float half_fov)
{
	draw_border_arc(f, cx, cy, half_fov);
	draw_border_line(f, cx, cy, -M_PI_2f - half_fov);
	draw_border_line(f, cx, cy, -M_PI_2f + half_fov);
}

static t_vec2f	rotated_world_pos(t_vec2f player_pos, float yaw, t_vec2i p)
{
	const float	lx = (float)(p.x - MM_SIZE / 2) / (float)MM_SCALE;
	const float	ly = (float)(p.y - MM_SIZE / 2) / (float)MM_SCALE;
	const float	cos_a = cosf(yaw + (float)M_PI_2);
	const float	sin_a = sinf(yaw + (float)M_PI_2);
	t_vec2f		world_pos;

	world_pos.x = floorf(player_pos.x + lx * cos_a - ly * sin_a);
	world_pos.y = floorf(player_pos.y + lx * sin_a + ly * cos_a);
	return (world_pos);
}

void	draw_minimap(t_image *f, const t_world *w, const t_assets *a)
{
	t_vec2i			p;
	t_vec2f			world_pos;
	const int32_t	half_sz = MM_SIZE / 2;
	const t_vec2i	begin = {{(int32_t)f->width / 2 - half_sz,
		(int32_t)f->height - half_sz}};
	const float		half_fov = w->player.fov / 2;

	p.y = -1;
	while (++p.y < MM_SIZE / 2)
	{
		p.x = -1;
		while (++p.x < MM_SIZE)
		{
			if (!in_fov(p.x - half_sz, p.y - half_sz, half_sz, half_fov))
				continue ;
			world_pos = rotated_world_pos(w->player.pos, w->player.yaw, p);
			set_pixel((uint32_t)(begin.x + p.x), (uint32_t)(begin.y + p.y),
				get_tile_color(&a->map, a->tiles, (int32_t)world_pos.x,
					(int32_t)world_pos.y), f);
		}
	}
	draw_border(f, (uint32_t)begin.x + half_sz, (uint32_t)begin.y + half_sz, half_fov);
}
