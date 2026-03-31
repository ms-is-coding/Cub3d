/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:49:02 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/31 20:13:37 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdatomic.h>

#include "world/world.h"

#include "physics.h"
#include "physics_internal.h"

void	physics_update(t_physics *p, float dt)
{
	t_world			*world;
	const t_world	*ready;

	if (!p || !p->world_buffer || !p->input)
		return ;
	world = world_get_write_snapshot(p->world_buffer);
	ready = world_get_ready_snapshot(p->world_buffer);
	world_copy_snapshot(world, ready);
	(void)dt;
	world->tick++;
	player_update(world, p->assets, p->input);
	entities_update(world, p->input, dt);
	world_publish_snapshot(p->world_buffer);
	debug_print_steps_per_sec();
}
