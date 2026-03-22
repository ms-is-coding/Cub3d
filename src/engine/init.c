/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:31:29 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 19:04:37 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "gfx/gfx.h"
#include "assets/assets.h"
#include "hooks/hooks.h"
#include "world/world.h"
#include "physics/physics.h"
#include "renderer/renderer.h"

#include "engine.h"

#ifdef DEBUG

# include <stdio.h>

static void	debug_print_engine(t_engine *e)
{
	dprintf(2, "\n\t=== Engine Debug Info ===\n");
	debug_print_options(&e->opt);
	debug_print_assets(&e->assets);
	dprintf(2, "\n\t=========================\n");
}

#else

static void	debug_print_engine(t_engine *e)
{
	(void)e;
}

#endif

static void	init_engine_pointers(t_engine *e)
{
	e->physics.world_buffer = &e->world_buffer;
	e->renderer.world_buffer = &e->world_buffer;
	e->assets.gfx = &e->gfx;
	e->renderer.options = &e->opt;
	e->renderer.gfx = &e->gfx;
	e->renderer.assets = &e->assets;
	e->physics.input = &e->input;
	e->physics.assets = &e->assets;
}

int	engine_init(t_engine *e, int argc, char **argv)
{
	memset(e, 0, sizeof(t_engine));
	if (options_init(&e->opt, argc, argv))
		return (1);
	init_engine_pointers(e);
	if (gfx_init(&e->gfx, &e->opt)
		|| assets_init(&e->assets, e->opt.file_path)
		|| hooks_init(e)
		|| world_buffer_init(&e->world_buffer, &e->assets)
		|| physics_init(&e->physics)
		|| renderer_init(&e->renderer, &e->opt))
	{
		engine_deinit(e);
		return (1);
	}
	debug_print_engine(e);
	return (0);
}
