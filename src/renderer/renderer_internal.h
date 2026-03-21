/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:38:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/21 17:03:29 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERNAL_H
# define RENDERER_INTERNAL_H

# include <stdint.h>

# include "gfx/gfx.h"
# include "world/world.h"
# include "renderer.h"
# include "utils/vectors.h"

typedef struct s_render_task {
	t_renderer		*renderer;
	const t_world	*world;
	t_image			*frame;
	uint32_t		x_start;
	uint32_t		x_end;
}	t_render_task;

typedef struct s_dda
{
	t_vec2f	delta;
	t_vec2f	side;
	t_vec2i	step;
}	t_dda;

typedef struct s_ray
{
	t_dda		dda;
	t_vec2f		dir;
	t_vec2u		pos;
	float		dist;
	uint32_t	line_height;
	uint32_t	start;
	uint32_t	end;
	uint32_t	x;
	uint8_t		side;

	char		reserved[3];
}	t_ray;

typedef struct s_hit
{
	float	dist;
	float	wall_x;
	int		side;
	uint8_t	tile_id;

	char	reserved[3];
}	t_hit;

typedef struct s_col_params
{
	uint32_t	height;
	uint32_t	draw_start;
	uint32_t	draw_end;
	uint32_t	line_height;
	t_ray		*ray;
	t_hit		*hit;
	t_image		*tex;
}	t_col_params;

void	draw_minimap(t_image *f, const t_world *w, const t_assets *a);

int		cast_ray(t_ray *ray, t_hit *hit, t_render_task *task);

uint32_t	apply_fog(uint32_t color, float distance);

void	draw_ceiling(t_image *f, t_col_params p, uint32_t x, uint32_t color);
void	draw_floor(t_image *f, t_col_params p, uint32_t x, uint32_t color);
void	draw_wall(t_image *f, t_col_params p, uint32_t x);

void	draw_column(t_render_task *task, t_ray *ray, t_hit *hit);

#endif
