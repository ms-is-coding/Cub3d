/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:14:46 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/20 17:02:39 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "assets/assets.h"
#include "renderer.h"
#include "world/world.h"
#include "utils/utils.h"

#include "renderer_internal.h"

static void	init_dda(t_ray *ray, const t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->dda.step.x = -1;
		ray->dda.delta.x = fabsf(1.0f / ray->dir.x);
		ray->dda.side.x = (player.pos.x - (float)ray->pos.x) * ray->dda.delta.x;
	}
	else
	{
		ray->dda.step.x = 1;
		ray->dda.delta.x = fabsf(1.0f / ray->dir.x);
		ray->dda.side.x = ((float)ray->pos.x + 1.0f - player.pos.x) * ray->dda.delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->dda.step.y = -1;
		ray->dda.delta.y = fabsf(1.0f / ray->dir.y);
		ray->dda.side.y = (player.pos.y - (float)ray->pos.y) * ray->dda.delta.y;
	}
	else
	{
		ray->dda.step.y = 1;
		ray->dda.delta.y = fabsf(1.0f / ray->dir.y);
		ray->dda.side.y = ((float)ray->pos.y + 1.0f - player.pos.y) * ray->dda.delta.y;
	}
}

static void	init_ray(t_ray *ray, const t_player p, uint32_t width, uint32_t x)
{
	const float	cam = 2.0f * (float)x / (float)width - 1.0f;
	const float	dir_x = cosf(p.yaw);
	const float	dir_y = sinf(p.yaw);
	const float	plane = tanf(p.fov * 0.5f);

	ray->dir.x = dir_x - dir_y * cam * plane;
	ray->dir.y = dir_y + dir_x * cam * plane;
	ray->pos.x = (int32_t)p.pos.x;
	ray->pos.y = (int32_t)p.pos.y;
	init_dda(ray, p);
}

static int	cast_ray(t_ray *ray, const t_player *p, const t_map *map,
				const t_tile *tiles, t_hit *hit)
{
	int	found = 0;

	while (!found)
	{
		if (ray->dda.side.x < ray->dda.side.y)
		{
			ray->dda.side.x += ray->dda.delta.x;
			ray->pos.x += ray->dda.step.x;
			hit->side = 0;
		}
		else
		{
			ray->dda.side.y += ray->dda.delta.y;
			ray->pos.y += ray->dda.step.y;
			hit->side = 1;
		}

		/* bounds check */
		if (ray->pos.x < 0 || ray->pos.x >= (int)map->width
			|| ray->pos.y < 0 || ray->pos.y >= (int)map->height)
			return (0);

		hit->tile_id = map->data[ray->pos.y * map->width + ray->pos.x];

		if (tiles[hit->tile_id].flags & TILE_F_RAY_BLOCK)
			found = 1;
	}

	/* distance */
	if (hit->side == 0)
		hit->dist = (ray->pos.x - p->pos.x
				+ (1 - ray->dda.step.x) * 0.5f) / ray->dir.x;
	else
		hit->dist = (ray->pos.y - p->pos.y
				+ (1 - ray->dda.step.y) * 0.5f) / ray->dir.y;

	if (hit->dist < 0.001f)
		hit->dist = 0.001f;

	/* wall hit position */
	if (hit->side == 0)
		hit->wall_x = p->pos.y + hit->dist * ray->dir.y;
	else
		hit->wall_x = p->pos.x + hit->dist * ray->dir.x;

	hit->wall_x -= floorf(hit->wall_x);

	return (1);
}

static void	render_slice(t_render_task *task)
{
	uint32_t	x;
	t_ray		ray;
	t_hit		hit;

	x = task->x_start;
	while (x <= task->x_end)
	{
		init_ray(&ray, task->world->player, task->frame->width, x);
		if (cast_ray(&ray,
				&task->world->player,
				&task->renderer->assets->map,
				task->renderer->assets->tiles,
				&hit))
		{
			draw_column(task, x, &ray, &hit);
		}
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
