/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:56:21 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 21:29:05 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "assets/assets.h"
#include "world/world.h"
#include "common.h"

#include "physics/physics_internal.h"

static bool	is_solid(t_world *w, t_assets *a, t_vec2i p, t_hitbox *box)
{
	uint32_t	idx;
	uint8_t		tile_id;

	if (p.x < 0 || p.x >= (int32_t)a->map.width
		|| p.y < 0 || p.y >= (int32_t)a->map.height)
		return (true);
	idx = (uint32_t)p.y * (uint32_t)a->map.width + (uint32_t)p.x;
	tile_id = a->map.data[idx];
	box->x.e[0] = (int32_t)p.x;
	box->x.e[1] = (int32_t)p.x + 1;
	box->y.e[0] = (int32_t)p.y;
	box->y.e[1] = (int32_t)p.y + 1;
	if (a->tiles[tile_id].flags & TILE_F_DOOR)
		return (door_offset_at(w, (int32_t)p.x, (int32_t)p.y) < 0.6f);
	return (a->tiles[tile_id].flags & TILE_F_SOLID);
}

static void	move_axis_dir(t_player *p, t_hitbox box, int axis, int dir)
{
	const float	p_min = p->pos.e[axis] - ENTITY_SIZE / 2;
	const float	p_max = p->pos.e[axis] + ENTITY_SIZE / 2;
	int			other;

	if (p_max > (float)box.e[axis].e[0] && p_min < (float)box.e[axis].e[1])
	{
		other = !axis;
		if (p->pos.e[other] + ENTITY_SIZE / 2 > (float)box.e[other].e[0]
			&& p->pos.e[other] - ENTITY_SIZE / 2 < (float)box.e[other].e[1])
		{
			p->vel.e[axis] = 0;
			if (dir == 1)
				p->pos.e[axis] = (float)box.e[axis].e[0]
					- ENTITY_SIZE / 2 - 0.001f;
			else
				p->pos.e[axis] = (float)box.e[axis].e[1]
					+ ENTITY_SIZE / 2 + 0.001f;
		}
	}
}

void	apply_collision(t_world *world, t_assets *assets, int axis)
{
	t_hitbox	box;
	t_vec2i		p;
	int32_t		end;
	bool		dir;

	dir = world->player.vel.e[axis] > 0;
	p.e[!axis] = (int32_t)(world->player.pos.e[!axis] - ENTITY_SIZE / 2.0f) - 1;
	end = (int32_t)(world->player.pos.e[!axis] + ENTITY_SIZE / 2.0f) + 1;
	p.e[axis] = (int32_t)(world->player.pos.e[axis]
			+ ((float [2]){-1, 1}[dir] * ENTITY_SIZE / 2));
	while (++p.e[!axis] < end)
		if (is_solid(world, assets, p, &box))
			move_axis_dir(&world->player, box, axis, dir);
}
