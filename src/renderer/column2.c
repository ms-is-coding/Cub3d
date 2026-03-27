/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:50:44 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/28 00:26:40 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "gfx/gfx.h"

#include "renderer_internal.h"

static uint32_t	get_tex_x(t_image *tex, t_col_params p)
{
	uint32_t	x;
	float		wall_x;

	wall_x = p.hit->wall_x;
	if (wall_x < 0.0f)
		wall_x = 0.0f;
	else if (wall_x > 1.0f)
		wall_x = 1.0f;
	x = (uint32_t)(wall_x * (float)tex->width);
	if ((p.hit->side == 0 && p.ray->dir.x > 0)
		|| (p.hit->side == 1 && p.ray->dir.y < 0))
			x = tex->width - x - 1;
	return (x);
}

static uint32_t	get_tex_y(t_image *tex, float tex_pos)
{
	if (tex_pos < 0.0f)
		return (0);
	else if (tex->height <= (uint32_t)tex_pos)
		return (tex->height - 1);
	return ((uint32_t)tex_pos);
}

void	draw_ceiling(t_image *f, t_col_params p, uint32_t x, uint32_t color)
{
	float		dist;
	uint32_t	i;

	i = 0;
	while (i < p.draw_start)
	{
		dist = (float)p.height / (float)(p.height - 2 * i);
		set_pixel(x, i++, apply_fog(color, dist), f);
	}
}

void	draw_floor(t_image *f, t_col_params p, uint32_t x, uint32_t color)
{
	float		dist;
	uint32_t	i;

	i = p.draw_end;
	while (i < p.height)
	{
		dist = (float)p.height / (float)(2 * i - p.height);
		set_pixel(x, i++, apply_fog(color, dist), f);
	}
}

void	draw_wall(t_image *f, t_col_params p, uint32_t x)
{
	t_vec2u		tex_pos;
	uint32_t	color;
	uint32_t	y;
	float		step;
	float		tex_idx;

	if (p.line_height == 0)
		return ;
	tex_pos.x = get_tex_x(p.tex, p);
	step = (float)p.tex->height / (float)p.line_height;
	tex_idx = ((float)p.draw_start - (float)p.height / 2.0f
			+ (float)p.line_height / 2.0f) * step
		+ p.hit->offset * (float)p.tex->height;
	y = p.draw_start;
	while (y < p.draw_end)
	{
		tex_pos.y = get_tex_y(p.tex, tex_idx);
		color = p.tex->data[tex_pos.y * (p.tex->linesz / 4) + tex_pos.x];
		if (p.hit->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		color = apply_fog(color, p.hit->dist);
		set_pixel(x, y, color, f);
		tex_idx += step;
		y++;
	}
}
