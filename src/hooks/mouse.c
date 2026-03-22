/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:39:59 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 11:34:10 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "mlx.h"

#include "engine/engine.h"

#include "hooks_internal.h"

static int	mouse_move_hook(int x, int y, t_engine *e)
{
	int32_t	dx;
	int32_t	dy;

	if (!e)
		return (1);
	dx = (int32_t)x - e->input.mouse.last_x;
	dy = (int32_t)y - e->input.mouse.last_z;
	e->input.mouse.last_x = x;
	e->input.mouse.last_z = y;
	e->input.mouse.delta_x = dx;
	e->input.mouse.delta_z = dy;
	return (0);
}

static int	mouse_press_hook(int button, int x, int y, t_engine *e)
{
	(void)x;
	(void)y;
	if (!e)
		return (1);
	if (button == m_left)
		e->input.mouse.left_pressed = 1;
	else if (button == m_right)
		e->input.mouse.right_pressed = 1;
	else if (button == m_middle)
		e->input.mouse.middle_pressed = 1;
	return (0);
}

static int	mouse_release_hook(int button, int x, int y, t_engine *e)
{
	(void)x;
	(void)y;
	if (!e)
		return (1);
	if (button == m_left)
		e->input.mouse.left_pressed = 0;
	else if (button == m_right)
		e->input.mouse.right_pressed = 0;
	else if (button == m_middle)
		e->input.mouse.middle_pressed = 0;
	return (0);
}

int	hooks_mouse_init(t_engine *engine)
{
	if (!engine || !engine->gfx.win)
		return (1);
	if (mlx_hook(
			engine->gfx.win,
			evMotionNotify,
			evPointerMotionMask,
			(t_hook_fn)(intptr_t)mouse_move_hook,
		engine) < 0)
		return (1);
	if (mlx_hook(
			engine->gfx.win,
			evButtonPress,
			evButtonPressMask,
			(t_hook_fn)(intptr_t)mouse_press_hook,
		engine) < 0)
		return (1);
	if (mlx_hook(
			engine->gfx.win,
			evButtonRelease,
			evButtonReleaseMask,
			(t_hook_fn)(intptr_t)mouse_release_hook,
		engine) < 0)
		return (1);
	return (0);
}
