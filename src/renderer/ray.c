/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:56:20 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 10:50:42 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "assets/assets.h"
#include "renderer.h"
#include "world/world.h"

#include "renderer_internal.h"

static void	init_dda(t_ray *ray, const t_player player)
{
	ray->dda.step.x = 1 - 2 * (ray->dir.x < 0);
	ray->dda.delta.x = fabsf(1.0f / ray->dir.x);
	ray->dda.side.x = ((ray->dir.x < 0) * (player.pos.x - (float)ray->pos.x)
			+ (ray->dir.x >= 0) * ((float)ray->pos.x + 1.0f - player.pos.x))
		* ray->dda.delta.x;
	ray->dda.step.y = 1 - 2 * (ray->dir.y < 0);
	ray->dda.delta.y = fabsf(1.0f / ray->dir.y);
	ray->dda.side.y = ((ray->dir.y < 0) * (player.pos.y - (float)ray->pos.y)
			+ (ray->dir.y >= 0) * ((float)ray->pos.y + 1.0f - player.pos.y))
		* ray->dda.delta.y;
}

static void	init_ray(t_ray *ray, const t_player p, uint32_t width)
{
	const float	cam = 2.0f * (float)ray->x / (float)width - 1.0f;
	const float	dir_x = cosf(p.yaw);
	const float	dir_y = sinf(p.yaw);
	const float	plane = tanf(p.fov * 0.5f);

	ray->dir.x = dir_x - dir_y * cam * plane;
	ray->dir.y = dir_y + dir_x * cam * plane;
	ray->pos.x = (uint32_t)p.pos.x;
	ray->pos.y = (uint32_t)p.pos.y;
	init_dda(ray, p);
}

int	cast_ray(t_ray *ray, t_hit *hit, t_render_task *task)
{
	const t_player		p = task->world->player;
	const t_map			*map = &task->renderer->assets->map;
	const t_tile		*tiles = task->renderer->assets->tiles;

	init_ray(ray, p, task->frame->width);
	while (true)
	{
		hit->side = (ray->dda.side.x > ray->dda.side.y);
		ray->dda.side.e[hit->side] += ray->dda.delta.e[hit->side];
		ray->pos.e[hit->side] += (uint32_t)ray->dda.step.e[hit->side];
		if (ray->pos.x < 0 || ray->pos.x >= map->width
			|| ray->pos.y < 0 || ray->pos.y >= map->height)
			return (1);
		hit->tile_id = map->data[ray->pos.y * map->width + ray->pos.x];
		if (tiles[hit->tile_id].flags & TILE_F_RAY_BLOCK)
			break ;
	}
	hit->dist = ((float)ray->pos.e[hit->side] - p.pos.e[hit->side] + (float)(1
				- ray->dda.step.e[hit->side]) * 0.5f) / ray->dir.e[hit->side];
	if (hit->dist < 0.001f)
		hit->dist = 0.001f;
	hit->wall_x = p.pos.e[!hit->side] + hit->dist * ray->dir.e[!hit->side];
	hit->wall_x -= floorf(hit->wall_x);
	return (0);
}
