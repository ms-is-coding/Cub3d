/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:56:47 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 19:05:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

#ifdef DEBUG

# include <stddef.h>
# include <stdio.h>

void	debug_print_options(t_options *options)
{
	dprintf(2, "\t\t- OPTIONS -\n\n");
	dprintf(2, "- File path: %s\n", options->file_path);
	dprintf(2, "- Width: %u\n", options->width);
	dprintf(2, "- Height: %u\n", options->height);
	dprintf(2, "- Thread count: %d\n", options->thread_count);
	dprintf(2, "- FPS: %d\n\n", options->fps);
}

#else

void	debug_print_options(t_options *options)
{
	(void)options;
}

#endif
