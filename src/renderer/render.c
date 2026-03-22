/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:14:46 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 18:06:20 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "renderer.h"
#include "world/world.h"
#include "utils/utils.h"

#include "renderer_internal.h"

static void	render_slice(void *arg)
{
	t_ray			ray;
	t_hit			hit;
	t_render_task	*task;

	task = arg;
	ray.x = task->x_start;
	while (ray.x <= task->x_end)
	{
		if (cast_ray(&ray,
				&hit,
				task) == 0)
			draw_column(task, &ray, &hit);
		ray.x++;
	}
}

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
	draw_minimap(frame, world_get_ready_snapshot(r->world_buffer), r->assets);
}

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
	renderer_publish_frame(r);
	debug_print_fps(now);
}
