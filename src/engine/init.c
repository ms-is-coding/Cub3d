/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:31:29 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/17 11:07:49 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "engine.h"
#include "physics/physics.h"
#include "renderer/renderer.h"

#include <stdio.h>

int	engine_init(t_engine *e, int argc, char **argv)
{
	memset(e, 0, sizeof(t_engine));
	e->physics.world_buffer = &e->world_buffer;
	e->renderer.world_buffer = &e->world_buffer;
	e->renderer.gfx = &e->gfx;
	e->assets.mlx = &e->gfx.mlx;
	if (options_init(&e->opt, argc, argv)
		|| gfx_init(&e->gfx, &e->opt)
		|| assets_init(&e->assets, argv[argc - 1])
		|| world_buffer_init(&e->world_buffer)
		|| physics_init(&e->physics)
		|| renderer_init(&e->renderer, &e->opt))
	{
		printf("In here\n");
		engine_deinit(e);
		return (1);
	}
	return (0);
}
