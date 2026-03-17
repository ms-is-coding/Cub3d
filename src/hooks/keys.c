/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:50:19 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 12:28:02 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "mlx.h"

#include "cub3d.h"
#include "engine/engine.h"

#include "hooks.h"

enum e_key_bits {
	KEY_FORWARD,
	KEY_BACKWARD,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_YAW_LEFT,
	KEY_YAW_RIGHT,
	KEY_PITCH_UP,
	KEY_PITCH_DOWN,
	KEY_COUNT
};

static const int	g_keymap[KEY_COUNT] = {
[KEY_FORWARD] = k_w,
[KEY_BACKWARD] = k_s,
[KEY_LEFT] = k_a,
[KEY_RIGHT] = k_d,
[KEY_UP] = k_space,
[KEY_DOWN] = k_c,
[KEY_YAW_LEFT] = k_left,
[KEY_YAW_RIGHT] = k_right,
[KEY_PITCH_UP] = k_up,
[KEY_PITCH_DOWN] = k_down,
};

static inline void	key_update(uint32_t *bits, int keysym, uint32_t pressed)
{
	uint32_t	mask;
	uint32_t	match;
	uint8_t		i;

	i = 0;
	mask = 0;
	while (i < KEY_COUNT)
	{
		match = (keysym == g_keymap[i]);
		mask |= match << i;
		i++;
	}
	*bits ^= (-pressed ^ *bits) & mask;
}

static int	key_press_hook(int keysym, t_engine *e)
{
	key_update(&e->input.keys.bits, keysym, 1);
	return (0);
}

static int	key_release_hook(int keysym, t_engine *e)
{
	key_update(&e->input.keys.bits, keysym, 0);
	return (0);
}

int	hooks_keys_init(t_engine *engine)
{
	mlx_hook(engine->gfx.win, evKeyPress, evKeyPressMask,
		(t_hook_fn)(intptr_t)key_press_hook, engine);
	mlx_hook(engine->gfx.win, evKeyRelease, evKeyReleaseMask,
		(t_hook_fn)(intptr_t)key_release_hook, engine);
	return (0);
}
