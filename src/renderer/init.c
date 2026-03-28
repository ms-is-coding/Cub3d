/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:44:43 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 16:57:15 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "common.h"
#include "gfx/gfx.h"
#include "options/options.h"
#include "threads/threads.h"
#include "utils/error.h"

#include "renderer.h"

static int	renderer_init_framebuffers(t_renderer *r, const t_options *opt)
{
	int	i;

	i = 0;
	while (i < FRAMEBUFFER_COUNT)
	{
		r->framebuffers[i] = malloc(sizeof(t_image));
		if (!r->framebuffers[i]
			|| gfx_image_create(
				r->gfx->mlx,
				r->framebuffers[i],
				opt->width,
				opt->height) != 0)
		{
			free(r->framebuffers[i]);
			while (i-- > 0)
				gfx_image_destroy(r->gfx->mlx, r->framebuffers[i]);
			return (print_error(MOD_RENDERER, ERR_IMG_CREATE, 1));
		}
		i++;
	}
	return (0);
}

int	renderer_init(t_renderer *r, const t_options *opt)
{
	if (renderer_init_framebuffers(r, opt))
		return (1);
	if (threadpool_init(&r->pool, (int *)(intptr_t) & opt->thread_count))
		return (1);
	if (opt->fps > 0)
	{
		r->fps_limit = opt->fps;
		r->frame_time_us = 1000000l / r->fps_limit;
	}
	else
	{
		r->fps_limit = 0;
		r->frame_time_us = 0;
	}
	return (0);
}
