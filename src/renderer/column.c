/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:17:19 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 14:53:17 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "assets/assets.h"
#include "gfx/gfx.h"

#include "renderer_internal.h"
#include "utils/vectors.h"

static void	init_params(t_col_params *p, t_ray *r, t_hit *h, uint32_t height)
{
	int32_t	visible;
	int32_t	bottom;
	int32_t	top;

	p->ray = r;
	p->hit = h;
	p->height = height;
	p->line_height = (uint32_t)((float)height / h->dist);
	visible = (int32_t)((float)p->line_height * (1.0f - h->offset));
	top = (int32_t)(height / 2 - p->line_height / 2);
	bottom = top + visible;
	if (top < 0)
		top = 0;
	if (bottom < 0)
		bottom = 0;
	if (bottom >= (int32_t)height)
		bottom = (int32_t)height;
	p->draw_start = (uint32_t)top;
	p->draw_end = (uint32_t)bottom;
}

t_dir	ray_to_dir(t_ray *ray, int side)
{
	t_dir	dir;

	dir = (t_dir)((!side << 1) + (ray->dir.e[side] < 0.0f) + 2);
	return (dir);
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

static void	draw_background_column(t_render_task *task, t_ray *ray)
{
	const t_assets	*assets = task->renderer->assets;
	const t_tile	*tile;
	t_col_params	p;
	t_hit			bg_hit;

	p.ray = ray;
	p.cam_pos = task->world->player.pos;
	p.tick = task->world->tick;
	if (cast_ray(ray, &bg_hit, task))
	{
		p.height = task->frame->height;
		p.draw_start = 0;
		p.draw_end = task->frame->height;
		draw_ceiling(task->frame, p, ray->x, assets);
		return ;
	}
	tile = &assets->tiles[bg_hit.tile_id];
	p.tex = tile_texture_at(tile, ray, bg_hit.side);
	if (!p.tex)
		p.tex = assets->asset_tex[TEX_INVALID];
	init_params(&p, ray, &bg_hit, task->frame->height);
	draw_ceiling(task->frame, p, ray->x, assets);
	draw_wall(task->frame, p, ray->x, tile);
	draw_floor(task->frame, p, ray->x, assets);
}

void	draw_column(t_render_task *task, t_ray *ray, t_hit *hit)
{
	const t_assets	*assets = task->renderer->assets;
	const t_tile	*tile = &assets->tiles[hit->tile_id];
	t_col_params	p;

	p.tex = tile_texture_at(tile, ray, hit->side);
	p.tick = task->world->tick;
	p.cam_pos = task->world->player.pos;
	if (!p.tex)
		p.tex = assets->asset_tex[TEX_INVALID];
	if (hit->is_door && hit->offset > 0.0f)
	{
		draw_background_column(task, ray);
		init_params(&p, ray, hit, task->frame->height);
		draw_wall(task->frame, p, ray->x, tile);
		return ;
	}
	init_params(&p, ray, hit, task->frame->height);
	draw_ceiling(task->frame, p, ray->x, assets);
	draw_wall(task->frame, p, ray->x, tile);
	draw_floor(task->frame, p, ray->x, assets);
}
