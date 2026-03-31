/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:46:27 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/30 21:27:47 by macarnie         ###   ########.fr       */
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
	t_player		*p;
	t_vec2f			d;
	float			len;
	struct s_values	k;

	p = &world->player;
	k = input->keys.values;
	d.x = (k.forward != 0) * cosf(p->yaw) - (k.backward != 0) * cosf(p->yaw)
		+ (k.left != 0) * sinf(p->yaw) - (k.right != 0) * sinf(p->yaw);
	d.y = (k.forward != 0) * sinf(p->yaw) - (k.backward != 0) * sinf(p->yaw)
		- (k.left != 0) * cosf(p->yaw) + (k.right != 0) * cosf(p->yaw);
	len = sqrtf(d.x * d.x + d.y * d.y);
	if (len > 0.0f)
	{
		p->vel.x += (d.x / len) * MOVE_SPEED;
		p->vel.y += (d.y / len) * MOVE_SPEED;
	}
	p->yaw_vel -= (k.yaw_left != 0) * ROT_SPEED;
	p->yaw_vel += (k.yaw_right != 0) * ROT_SPEED;
	p->fov = fmaxf(FOV_MIN, p->fov + (k.zoom_in != 0) * ZOOM_SPEED);
	p->fov = fminf(FOV_MAX, p->fov - (k.zoom_out != 0) * ZOOM_SPEED);
	world->player.yaw_vel += MOUSE_SENSITIVITY
		* (float)((input->mouse.delta_x != 0) * input->mouse.delta_x);
	input->mouse.delta_x = 0;
	input->mouse.delta_z = 0;
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
	apply_motion(world, assets);
}
