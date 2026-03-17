/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:47:32 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/20 13:39:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdint.h>

# if defined(__linux__)
#  include <X11/X.h>
#  include <X11/keysym.h>

enum {
	evDestroyNotify = DestroyNotify,
	evButtonPress = ButtonPress,
	evButtonPressMask = ButtonPressMask,
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
};

# elif defined(__APPLE__)

enum {
	evDestroyNotify = 17,
	evButtonPress = 4,
	evButtonPressMask = 1L << 2,
	evKeyPress = 2,
	evKeyPressMask = 1L << 0,
	evKeyRelease = 3,
	evKeyReleaseMask = 1L << 1,
	k_w = 13,
	k_s = 1,
	k_a = 0,
	k_d = 2,
	k_space = 49,
	k_esacpe = 53,
	k_c = 8,
	k_left = 123,
	k_right = 124,
	k_up = 126,
	k_down = 125,
};

# endif

#endif
