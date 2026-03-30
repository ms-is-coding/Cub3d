/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:45:47 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 19:39:18 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "assets/assets.h"
#include "renderer/renderer.h"
#include "gfx/gfx.h"
#include "physics/physics.h"
#include "world/world.h"
#include "physics/physics.h"

#include "engine.h"

#include <stdio.h>

void	engine_deinit(t_engine *e)
{
	if (!e)
		return ;
	world_buffer_deinit(&e->world_buffer);
	physics_deinit(&e->physics);
	renderer_deinit(&e->renderer);
	assets_deinit(&e->assets);
	gfx_deinit(&e->gfx);
	ft_memset(e, 0, sizeof(t_engine));
}
