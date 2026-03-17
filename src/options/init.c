/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:39:13 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 12:34:47 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "options/options.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

t_option		g_options[] = {
{
	.name = "--threads",
	.short_name = "-j",
	.offset = offsetof(t_options, thread_count),
	.max = MAX_THREADS,
	.min = 0,
	.parse = options_parse_i16,
}, {
	.name = "--width",
	.short_name = "-W",
	.offset = offsetof(t_options, width),
	.max = MAX_WIDTH,
	.min = 1,
	.parse = options_parse_u32,
}, {
	.name = "--height",
	.short_name = "-H",
	.offset = offsetof(t_options, height),
	.max = MAX_HEIGHT,
	.min = 1,
	.parse = options_parse_u32,
}, {
	.name = "--fps",
	.short_name = "-f",
	.offset = offsetof(t_options, fps),
	.max = MAX_FPS,
	.min = 0,
	.parse = options_parse_i16,
}
};

static void	init_default_values(t_options *opts)
{
	opts->thread_count = -1;
	opts->width = 800;
	opts->height = 600;
	opts->fps = 60;
}

int	options_init(t_options *opts, int argc, char **argv)
{
	int				i;
	size_t			j;
	const char		*option;
	const size_t	opt_count = sizeof(g_options) / sizeof(struct s_option);

	i = 1;
	init_default_values(opts);
	while (i < argc)
	{
		option = argv[i];
		j = -1lu;
		while (++j < opt_count)
			if (strcmp(g_options[j].name, option) == 0
				|| strcmp(g_options[j].short_name, option) == 0)
				break ;
		if (j == opt_count)
			return (argv[i + 1] != NULL);
		if (!argv[i + 1] || g_options[j].parse(opts, g_options[j], argv[i + 1]))
			return (1);
		i += 2;
	}
	return (argv[i] == NULL);
}
