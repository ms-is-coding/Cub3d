/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:50:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/21 21:32:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "mlx.h"

#include "engine/engine.h"

#include "hooks_internal.h"

static inline void	key_update(uint32_t *bits, int keysym, uint32_t pressed)
{
	uint32_t	mask;
	uint32_t	match;
	uint8_t		i;

	i = 0;
	mask = 0;
	while (i < KEY_COUNT)
	{
		match = 0;
		if (keysym == g_keymap[i])
			match = 1;
		mask |= match << i;
		i++;
	}
	*bits ^= (-pressed ^ *bits) & mask;
}

static int	key_press_hook(int keysym, t_engine *e)
{
	if (!e)
		return (1);
	key_update(&e->input.keys.bits, keysym, 1);
	if (keysym == k_escape)
		return (game_destroy_hook(e));
	return (0);
}

static int	key_release_hook(int keysym, t_engine *e)
{
	if (!e)
		return (1);
	key_update(&e->input.keys.bits, keysym, 0);
	return (0);
}

int	hooks_keys_init(t_engine *engine)
{
	if (!engine || !engine->gfx.win)
		return (1);
	if (mlx_hook(engine->gfx.win, evKeyPress, evKeyPressMask,
			(t_hook_fn)(intptr_t)key_press_hook, engine) < 0)
		return (1);
	if (mlx_hook(engine->gfx.win, evKeyRelease, evKeyReleaseMask,
			(t_hook_fn)(intptr_t)key_release_hook, engine) < 0)
		return (1);
	return (0);
}
