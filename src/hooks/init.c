/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:32:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 11:36:18 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"

#include "engine/engine.h"
#include "utils/error.h"

#include "hooks_internal.h"

int	game_destroy_hook(t_engine *e)
{
	if (!e)
		return (1);
	engine_deinit(e);
	exit(0);
	return (0);
}

#if defined(__linux__)

int	hooks_init(t_engine *engine)
{
	if (!engine || !engine->gfx.win)
		return (print_error(MOD_HOOKS, ERR_NULL_PTR, 1));
	if (mlx_hook(
			engine->gfx.win,
			evDestroyNotify,
			0,
			(t_hook_fn)(intptr_t)game_destroy_hook,
		engine) < 0)
		return (print_error(MOD_HOOKS, ERR_HOOKS, 1));
	if (hooks_keys_init(engine))
		return (print_error(MOD_HOOKS, ERR_HOOKS, 1));
	mlx_mouse_hide(engine->gfx.mlx, engine->gfx.win);
	if (hooks_mouse_init(engine))
		return (print_error(MOD_HOOKS, ERR_HOOKS, 1));
	return (0);
}

#elif defined(__APPLE__)

int	hooks_init(t_engine *engine)
{
	if (!engine || !engine->gfx.win)
		return (print_error(MOD_HOOKS, ERR_NULL_PTR, 1));
	if (mlx_hook(
			engine->gfx.win,
			evDestroyNotify,
			0,
			(t_hook_fn)(intptr_t)game_destroy_hook,
		engine) < 0)
		return (print_error(MOD_HOOKS, ERR_HOOKS, 1));
	if (hooks_keys_init(engine))
		return (print_error(MOD_HOOKS, ERR_HOOKS, 1));
	mlx_mouse_hide();
	if (hooks_mouse_init(engine))
		return (print_error(MOD_HOOKS, ERR_HOOKS, 1));
	return (0);
}

#endif
