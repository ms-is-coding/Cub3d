/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 21:26:26 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/31 16:00:11 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

#include <stdio.h>

const t_world	*world_get_ready_snapshot(const t_world_buffer *wb)
{
	const int	idx = atomic_load(&wb->ready_index);

	return (&wb->worlds[idx]);
}

t_world	*world_get_write_snapshot(t_world_buffer *wb)
{
	return (&wb->worlds[wb->write_index]);
}

void	world_copy_snapshot(t_world *dst, const t_world *src)
{
	uint32_t	i;

	dst->player = src->player;
	dst->entity_count = src->entity_count;
	dst->tick = src->tick;
	i = 0;
	while (i < src->entity_count)
	{
		dst->entities[i] = src->entities[i];
		i++;
	}
}

void	world_publish_snapshot(t_world_buffer *wb)
{
	int	ready_idx;
	int	next_write;

	if (!wb)
		return ;
	ready_idx = atomic_load(&wb->ready_index);
	next_write = (wb->write_index + 1) % WORLD_COUNT;
	while (next_write == ready_idx)
		next_write = (next_write + 1) % WORLD_COUNT;
	atomic_store(&wb->ready_index, wb->write_index);
	wb->write_index = next_write;
}
