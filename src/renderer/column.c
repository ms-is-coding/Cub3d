/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:17:19 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 10:41:13 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "assets/assets.h"
#include "gfx/gfx.h"

#include "renderer_internal.h"
#include "utils/vectors.h"

static void	init_params(t_col_params *p, t_ray *r, t_hit *h, uint32_t height)
{
	p->ray = r;
	p->hit = h;
	p->height = height;
	p->line_height = (uint32_t)((float)height / h->dist);
	p->draw_start = 0;
	p->draw_end = height - 1;
	if (p->line_height < height)
		p->draw_start = height / 2 - p->line_height / 2;
	if (p->draw_end < height)
		p->draw_end = height / 2 + p->line_height / 2;
}

static t_image	*tile_texture_at(const t_tile *tile, t_ray *ray, int side)
{
	t_dir	dir;

	dir = (t_dir)((!side << 1) + (ray->dir.e[side] < 0.0f) + 2);
	if (tile->textures[dir])
		return (tile->textures[dir]);
	if (tile->textures[DIR_DEFAULT])
		return (tile->textures[DIR_DEFAULT]);
	return (tile->textures[DIR_INVALID]);
}

void	draw_column(t_render_task *task, t_ray *ray, t_hit *hit)
{
	const t_assets	*assets = task->renderer->assets;
	const t_tile	*tile = &assets->tiles[hit->tile_id];
	t_col_params	p;

	p.tex = tile_texture_at(tile, ray, hit->side);
	if (!p.tex)
		p.tex = assets->invalid;
	init_params(&p, ray, hit, task->frame->height);
	draw_ceiling(task->frame, p, ray->x, assets->ceiling);
	draw_wall(task->frame, p, ray->x);
	draw_floor(task->frame, p, ray->x, assets->floor);
}
