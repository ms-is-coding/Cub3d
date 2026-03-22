/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:18:33 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:36:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_INTERNAL_H
# define HOOKS_INTERNAL_H

# include <stdbool.h>
# include <stdint.h>

# include "engine/engine.h"

# if defined(__linux__)
#  include <X11/X.h>
#  include <X11/keysym.h>

enum {
	evDestroyNotify = DestroyNotify,
	evMotionNotify = MotionNotify,
	evPointerMotionMask = PointerMotionMask,
	evButtonPress = ButtonPress,
	evButtonPressMask = ButtonPressMask,
	evButtonRelease = ButtonRelease,
	evButtonReleaseMask = ButtonReleaseMask,
	evKeyPress = KeyPress,
	evKeyPressMask = KeyPressMask,
	evKeyRelease = KeyRelease,
	evKeyReleaseMask = KeyReleaseMask,
	k_w = XK_w,
	k_s = XK_s,
	k_a = XK_a,
	k_d = XK_d,
	k_space = XK_space,
	k_escape = XK_Escape,
	k_c = XK_c,
	k_left = XK_Left,
	k_right = XK_Right,
	k_up = XK_Up,
	k_down = XK_Down,
	m_left = 1,
	m_right = 3,
	m_middle = 2,
};

# elif defined(__APPLE__)

enum {
	evDestroyNotify = 17,
	evMotionNotify = 6,
	evPointerMotionMask = 1L << 6,
	evButtonPress = 4,
	evButtonPressMask = 1L << 2,
	evButtonRelease = 5,
	evButtonReleaseMask = 1L << 3,
	evKeyPress = 2,
	evKeyPressMask = 1L << 0,
	evKeyRelease = 3,
	evKeyReleaseMask = 1L << 1,
	k_w = 13,
	k_s = 1,
	k_a = 0,
	k_d = 2,
	k_space = 49,
	k_escape = 53,
	k_c = 8,
	k_left = 123,
	k_right = 124,
	k_up = 126,
	k_down = 125,
	m_left = 1,
	m_right = 2,
	m_middle = 3,
};

# endif

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
	KEY_ESCAPE,
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
[KEY_ESCAPE] = k_escape,
};

int	hooks_keys_init(t_engine *engine);
int	hooks_mouse_init(t_engine *engine);

int	game_destroy_hook(t_engine *e);

#endif
