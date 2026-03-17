/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:39:59 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 16:37:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "hooks.h"
#include "mlx.h"
#include "engine/engine.h"

static int	on_mouse_down(int button, int x, int y, t_engine *e)
{
	// todo
	(void)button;
	(void)x;
	(void)y;
	(void)e;
	return (0);
}

int	hooks_mouse_init(t_engine *engine)
{
	mlx_hook(engine->gfx.win, evButtonPress, evButtonPressMask,
		(t_hook_fn)(intptr_t)on_mouse_down, engine);
	return (0);
}
