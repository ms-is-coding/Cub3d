/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:14:46 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 16:35:47 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "assets/assets.h"
#include "libft.h"
#include "renderer.h"
#include "world/world.h"
#include "utils/utils.h"

#include "renderer_internal.h"


//need to rework logic with t_assets func
//__attribute__((unused))
// static void	find_wall(t_ray *ray, t_map *map)
// {
// 	int	wall;

// 	wall = 0;
// 	while (!wall)
// 	{
// 		if (ray->dda.side_x < ray->dda.side_y)
// 		{
// 			ray->dda.side_x += ray->dda.delta_x;
// 			ray->pos_x += ray->dda.step_x;
// 			ray->side = DIR_EAST;
// 		}
// 		else
// 		{
// 			ray->dda.side_y += ray->dda.delta_y;
// 			ray->pos_y += ray->dda.step_y;
// 			ray->side = DIR_NORTH;
// 		}
// 		if (ray->pos_y < 0 || (uint32_t)ray->pos_y >= map->width)
// 			wall = 1;
// 		else if (ray->pos_x < 0
// 			|| (uint32_t)ray->pos_x >= map->width)
// 			wall = 1;
// 		else if (!wall && map[ray->pos_y][ray->pos_x] == '1')
// 			wall = 1;
// 	}
// 	calculate_distances(ray);
// }

static void	init_dda(t_ray *ray, const t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->dda.step_x = -1;
		ray->dda.delta_x = fabsf(1.0f / ray->dir.x);
		ray->dda.side_x = (player.pos.x - (float)ray->pos_x) * ray->dda.delta_x;
	}
	else
	{
		ray->dda.step_x = 1;
		ray->dda.delta_x = fabsf(1.0f / ray->dir.x);
		ray->dda.side_x = ((float)ray->pos_x + 1.0f - player.pos.x) * ray->dda.delta_x;
	}
	if (ray->dir.y < 0)
	{
		ray->dda.step_y = -1;
		ray->dda.delta_y = fabsf(1.0f / ray->dir.y);
		ray->dda.side_y = (player.pos.y - (float)ray->pos_y) * ray->dda.delta_y;
	}
	else
	{
		ray->dda.step_y = 1;
		ray->dda.delta_y = fabsf(1.0f / ray->dir.y);
		ray->dda.side_y = ((float)ray->pos_y + 1.0f - player.pos.y) * ray->dda.delta_y;
	}
}

static void	init_ray(t_ray *ray, const t_player player, uint32_t x)
{
	const float	cam = 2.0f * (float)x / (float)WIDTH - 1.0f;
	const float	dir_x = cosf(player.yaw);
	const float	dir_y = sinf(player.yaw);
	const float	plane = tanf(player.fov * 0.5f);

	ray->dir.x = dir_x - dir_y * cam * plane;
	ray->dir.y = dir_y + dir_x * cam * plane;
	ray->pos_x = (int)player.pos.x;
	ray->pos_y = (int)player.pos.y;
	init_dda(ray, player);
}

static void	render_slice(t_render_task *task)
{
	uint32_t		x;
	t_ray			ray;

	x = task->x_start;
	while (x <= task->x_end)
	{
		init_ray(&ray, task->world->player, x);
		x++;
	}
}

__attribute__((unused))
static void	renderer_dispatch_tasks(t_renderer *r)
{
	t_image			*frame;
	t_render_task	tasks[MAX_TASKS];
	uint32_t		chunk;
	uint32_t		t;

	frame = renderer_get_render_frame(r);
	chunk = (uint32_t)(((int)frame->width + r->pool.thread_count - 1)
			/ r->pool.thread_count);
	t = 0;
	while (t < (uint32_t)r->pool.thread_count)
	{
		tasks[t].renderer = r;
		tasks[t].world = world_get_ready_snapshot(r->world_buffer);
		tasks[t].frame = frame;
		tasks[t].x_start = t * chunk;
		tasks[t].x_end = (t + 1) * chunk - 1;
		if (tasks[t].x_end >= frame->width)
			tasks[t].x_end = frame->width - 1;
		threadpool_add(&r->pool, (void (*)(void *))(intptr_t)render_slice,
			&tasks[t]);
		t++;
	}
	threadpool_run(&r->pool);
}

static long		last_fps_time = 0;
static int		frame_count = 0;

void	renderer_render(t_renderer *r)
{
	const long		now = get_timestamp_us();
	long			sleep_us;
	struct timespec	ts;

	if (r->fps_limit > 0)
	{
		if (r->next_frame_time == 0)
			r->next_frame_time = now;
		sleep_us = r->next_frame_time - now;
		if (sleep_us > 0)
		{
			ts.tv_sec = sleep_us / 1000000l;
			ts.tv_nsec = (sleep_us % 1000000l) * 1000l;
			nanosleep(&ts, NULL);
		}
		else if (sleep_us < -r->frame_time_us)
			r->next_frame_time = now;
		r->next_frame_time += r->frame_time_us;
	}
	renderer_dispatch_tasks(r);
	// DEBUG FPS
	frame_count++;
	if (last_fps_time == 0)
		last_fps_time = now;
	if (now - last_fps_time >= 1000000L) // 1 second
	{
		double fps = (double)frame_count * 1000000.0
			/ (double)(now - last_fps_time);
		dprintf(2, "FPS: %.2f\n", fps);
		frame_count = 0;
		last_fps_time = now;
	}
	renderer_publish_frame(r);
}
