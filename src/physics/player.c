/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:46:27 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/28 19:32:52 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "assets/assets.h"
#include "world/world.h"
#include "hooks/hooks.h"
#include "common.h"

#include "physics/physics_internal.h"

static void	apply_keys_input(t_world *world, t_input *input)
{
	t_player	*p;
	t_keys		k;
	t_vec2f		d;
	float		len;

	p = &world->player;
	k = input->keys;
	d.x = (k.values.forward != 0) * cosf(p->yaw)
		- (k.values.backward != 0) * cosf(p->yaw)
		+ (k.values.left != 0) * sinf(p->yaw)
		- (k.values.right != 0) * sinf(p->yaw);
	d.y = (k.values.forward != 0) * sinf(p->yaw)
		- (k.values.backward != 0) * sinf(p->yaw)
		- (k.values.left != 0) * cosf(p->yaw)
		+ (k.values.right != 0) * cosf(p->yaw);
	len = sqrtf(d.x * d.x + d.y * d.y);
	if (len > 0.0f)
	{
		p->vel.x += (d.x / len) * MOVE_SPEED;
		p->vel.y += (d.y / len) * MOVE_SPEED;
	}
	p->yaw_vel -= (k.values.yaw_left != 0) * ROT_SPEED;
	p->yaw_vel += (k.values.yaw_right != 0) * ROT_SPEED;
	p->fov = fmaxf(FOV_MIN, p->fov + (k.values.zoom_in != 0) * ZOOM_SPEED);
	p->fov = fminf(FOV_MAX, p->fov - (k.values.zoom_out != 0) * ZOOM_SPEED);
}

static void	apply_mouse_input(t_world *world, t_input *input)
{
	world->player.yaw_vel += MOUSE_SENSITIVITY
		* (float)((input->mouse.delta_x != 0) * input->mouse.delta_x);
	input->mouse.delta_x = 0;
	input->mouse.delta_z = 0;
}

typedef union u_hitbox {
	struct {
		t_vec2i	x;
		t_vec2i	y;
	};
	t_vec2i	e[2];
}	t_hitbox;

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

static void	apply_collision(t_world *world, t_assets *assets, int axis)
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

static void	apply_motion(t_world *world, t_assets *assets)
{
	world->player.yaw += world->player.yaw_vel;
	world->player.yaw_vel *= FRICTION;
	world->player.pos.x += world->player.vel.x;
	apply_collision(world, assets, 0);
	world->player.vel.x *= FRICTION;
	world->player.pos.y += world->player.vel.y;
	apply_collision(world, assets, 1);
	world->player.vel.y *= FRICTION;
	if (world->player.pos.x < 0
		|| world->player.pos.y < 0
		|| world->player.pos.x >= (float)assets->map.width
		|| world->player.pos.y >= (float)assets->map.height)
	{
		world->player.pos.x = (float)(assets->map.player_pos
				% assets->map.width) + 0.5f;
		world->player.pos.y = (float)(assets->map.player_pos
				/ assets->map.width) + 0.5f;
		world->player.vel.x = 0;
		world->player.vel.y = 0;
	}
}

void	player_update(t_world *world, t_assets *assets, t_input *input)
{
	apply_keys_input(world, input);
	apply_mouse_input(world, input);
	apply_motion(world, assets);
}
