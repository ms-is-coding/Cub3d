/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/31 14:51:36 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "assets/assets.h"
#include "gfx/gfx.h"

#include "renderer_internal.h"

static uint32_t	sample_plane(t_image *tex, t_col_params p, float dist)
{
	float	wx;
	float	wy;

	wx = p.cam_pos.x + dist * p.ray->dir.x;
	wy = p.cam_pos.y + dist * p.ray->dir.y;
	wx -= floorf(wx);
	wy -= floorf(wy);
	return (tex->data[(uint32_t)(wy * (float)tex->height)
		* (tex->linesz / 4) + (uint32_t)(wx * (float)tex->width)]);
}

void	draw_ceiling(t_image *f, t_col_params p, uint32_t x, const t_assets *a)
{
	float		dist;
	uint32_t	color;
	uint32_t	i;

	i = 0;
	while (i < p.draw_start)
	{
		dist = (float)p.height / (float)(p.height - 2 * i);
		if (a->asset_tex[TEX_CEILING])
			color = sample_plane(a->asset_tex[TEX_CEILING], p, dist);
		else
			color = a->ceiling;
		set_pixel(x, i++, apply_fog(color, dist), f);
	}
}

void	draw_floor(t_image *f, t_col_params p, uint32_t x, const t_assets *a)
{
	float		dist;
	uint32_t	color;
	uint32_t	i;

	i = p.draw_end;
	while (i < p.height)
	{
		dist = (float)p.height / (float)(2 * i - p.height);
		if (a->asset_tex[TEX_FLOOR])
			color = sample_plane(a->asset_tex[TEX_FLOOR], p, dist);
		else
			color = a->floor;
		set_pixel(x, i++, apply_fog(color, dist), f);
	}
}
