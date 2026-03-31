/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/31 14:58:52 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "assets/assets.h"
#include "utils/error.h"
#include "../../lib/libft/libft.h"

#include "world.h"
#include <stddef.h>

static void	set_player(t_world *world, const t_map *map)
{
	world->player = (t_player){0};
	world->player.pos.x = (float)(map->player_pos % map->width) + 0.5f;
	world->player.pos.y = (float)(map->player_pos / map->width) + 0.5f;
	world->player.vel.x = 0.0f;
	world->player.vel.y = 0.0f;
	world->player.width = ENTITY_SIZE * 2.0f;
	world->player.height = ENTITY_SIZE * 2.0f;
	world->player.yaw
		= (map->data[map->player_pos] + 32 == 'N') * (float)(3.0 * M_PI_2)
		+ (map->data[map->player_pos] + 32 == 'S') * (float)(1.0 * M_PI_2)
		+ (map->data[map->player_pos] + 32 == 'E') * 0.0f
		+ (map->data[map->player_pos] + 32 == 'W') * (float)M_PI;
	world->player.yaw_vel = 0.0f;
	world->player.fov = (float)M_PI_2 * 0.9f;
}

static int	set_entities(t_world *world, const t_map *map, const t_tile *tiles)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (tiles[map->data[y * map->width + x]].flags & TILE_F_ENTITY)
			{
				if (world->entity_count >= MAX_ENTITIES)
					return (print_error(MOD_WORLD, ERR_ENTITY_LIMIT, 1));
				world->entities[world->entity_count].type = ENTITY_DOOR;
				world->entities[world->entity_count].pos.x = (float)x + 0.5f;
				world->entities[world->entity_count].pos.y = (float)y + 0.5f;
				world->entities[world->entity_count].door.state = DOOR_CLOSED;
				world->entities[world->entity_count].door.offset = 0.0f;
				world->entity_count++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	world_buffer_init(t_world_buffer *wb, t_assets *a)
{
	size_t	i;

	if (!wb || !a)
		return (print_error(MOD_WORLD, ERR_NULL_PTR, 1));
	set_player(&wb->worlds[0], &a->map);
	if (set_entities(&wb->worlds[0], &a->map, a->tiles))
		return (1);
	i = 1;
	while (i < WORLD_COUNT)
		ft_memcpy(&wb->worlds[i++], &wb->worlds[0], sizeof(t_world));
	atomic_store(&wb->ready_index, 0);
	wb->write_index = 1;
	return (0);
}
