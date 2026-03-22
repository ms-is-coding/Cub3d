/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 18:02:05 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 18:08:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

#ifdef DEBUG

# include <stdio.h>

# include "utils/utils.h"

void	debug_print_steps_per_sec(void)
{
	static long	last_step_time = 0;
	static int	step_count = 0;
	long		now;
	double		steps_per_sec;

	step_count++;
	now = get_timestamp_us();
	if (last_step_time == 0)
		last_step_time = now;
	if (now - last_step_time >= 1000000L)
	{
		steps_per_sec = (double)step_count * 1000000.0
			/ (double)(now - last_step_time);
		dprintf(2, "Engine Steps/s: %.2f\n", steps_per_sec);
		step_count = 0;
		last_step_time = now;
	}
}

#else

void	debug_print_steps_per_sec(void)
{
	return ;
}

#endif
