/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:32:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 16:36:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "cub3d.h"
#include "engine/engine.h"

#include "hooks.h"

static int	game_destroy_hook(t_engine *e)
{
	engine_deinit(e);
	return (0);
}

#if defined(__linux__)

int	hooks_init(t_engine *engine)
{
	// if (!game->win)
	// 	return (1);
	mlx_hook(engine->gfx.win, evDestroyNotify, 0,
		(t_hook_fn)(intptr_t)game_destroy_hook, engine);
	hooks_keys_init(engine);
	mlx_mouse_hide(engine->gfx.mlx, engine->gfx.win);
	hooks_mouse_init(engine);
	return (0);
}

#elif defined(__APPLE__)

int	hooks_init(t_engine *engine)
{
	if (!engine->gfx.win)
		return (1);
	mlx_hook(engine->gfx.win, evDestroyNotify, 0,
		(t_hook_fn)(intptr_t)game_destroy_hook, engine);
	hooks_keys_init(engine);
	mlx_mouse_hide();
	hooks_mouse_init(engine);
	return (0);
}

#endif
