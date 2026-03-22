/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:46:03 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 11:36:52 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>

#include "physics.h"
#include "world/world.h"
#include "utils/utils.h"
#include "utils/error.h"

__attribute__((always_inline))
inline void	sleep_ns(long ns)
{
	struct timespec	ts;

	ts.tv_sec = 0;
	ts.tv_nsec = ns;
	nanosleep(&ts, NULL);
}

static void	*physics_thread(t_physics *p)
{
	long			last_time_us;
	float			accumulator;
	const float		dt = 1.0f / 128.0f;
	long			now_us;
	float			elapsed_s;

	last_time_us = get_timestamp_us();
	accumulator = 0.0f;
	while (atomic_load(&p->running))
	{
		now_us = get_timestamp_us();
		elapsed_s = (float)(now_us - last_time_us) / 1000000.0f;
		last_time_us = now_us;
		accumulator += elapsed_s;
		while (accumulator >= dt && atomic_load(&p->running))
		{
			physics_update(p, dt);
			accumulator -= dt;
		}
		sleep_ns(1000L);
	}
	return (NULL);
}

int	physics_init(t_physics *p)
{
	if (!p || !p->world_buffer || !p->input)
		return (print_error(MOD_PHYSICS, ERR_NULL_PTR, 1));
	world_get_write_snapshot(p->world_buffer);
	world_get_write_snapshot(p->world_buffer);
	atomic_store(&p->running, 1);
	if (pthread_create(
			&p->thread,
			NULL,
			(void *(*)(void *))(intptr_t)physics_thread,
		p) != 0)
		return (print_error(MOD_PHYSICS, ERR_PERROR, 1));
	return (0);
}
