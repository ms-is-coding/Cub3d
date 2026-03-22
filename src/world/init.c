/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 10:57:43 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "assets/assets.h"
#include "utils/error.h"

#include "world.h"
#include <stddef.h>

static void	set_player(t_world *world, const t_map *map)
{
	world->player.pos.x = (float)(map->player_pos % map->width) + 0.5f;
	world->player.pos.y = (float)(map->player_pos / map->width) + 0.5f;
	world->player.vel.x = 0.0f;
	world->player.vel.y = 0.0f;
	world->player.yaw = (map->data[map->player_pos] == 'N') * 270.0f
		+ (map->data[map->player_pos] == 'S') * 90.0f
		+ (map->data[map->player_pos] == 'E') * 0.0f
		+ (map->data[map->player_pos] == 'W') * 180.0f;
	world->player.yaw_vel = 0.0f;
	world->player.fov = 90.0f;
}

int	world_buffer_init(t_world_buffer *wb, t_assets *a)
{
	size_t	i;

	if (!wb || !a)
		return (print_error(MOD_WORLD, ERR_NULL_PTR, 1));
	i = 0;
	while (i < WORLD_COUNT)
		set_player(&wb->worlds[i++], &a->map);
	atomic_store(&wb->ready_index, 0);
	wb->write_index = 1;
	return (0);
}
