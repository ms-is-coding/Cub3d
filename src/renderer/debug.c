/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:05:34 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 18:06:43 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer_internal.h"

#ifdef DEBUG

# include <stdio.h>

void	debug_print_fps(double now)
{
	static long		last_fps_time = 0;
	static int		frame_count = 0;
	double			fps;

	frame_count++;
	if (last_fps_time == 0)
		last_fps_time = (long)now;
	if (now - last_fps_time >= 1000000L)
	{
		fps = (double)frame_count * 1000000.0
			/ (double)(now - last_fps_time);
		dprintf(2, "FPS: %.2f\n", fps);
		frame_count = 0;
		last_fps_time = (long)now;
	}
}

#else

void	debug_print_fps(double now)
{
	(void)now;
}

#endif
