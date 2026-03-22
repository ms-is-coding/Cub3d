/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:45:00 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 10:57:20 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx/gfx.h"

#include "renderer.h"
#include "threads/threads.h"

void	renderer_deinit(t_renderer *r)
{
	int	i;

	if (!r)
		return ;
	i = 0;
	while (i < FRAMEBUFFER_COUNT)
	{
		gfx_image_destroy(r->gfx->mlx, &r->framebuffers[i]);
		i++;
	}
	threadpool_deinit(&r->pool);
}
