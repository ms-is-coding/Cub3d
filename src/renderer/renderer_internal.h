/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:38:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/30 21:49:11 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERNAL_H
# define RENDERER_INTERNAL_H

# include <stdint.h>

# include "gfx/gfx.h"
# include "world/world.h"
# include "renderer.h"
# include "utils/vectors.h"

# define MM_SIZE	256
# define MM_SCALE	20
# define MM_WALL	0x00FFFFFF
# define MM_DOOR	0x00FFFF00
# define MM_FLOOR	0x00333333
# define MM_OOB		0x00111111
# define MM_BORDER	0x00FF0000

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
	float	offset;
	int		side;
	uint8_t	tile_id;
	bool	is_door;

	char	reserved[2];
}	t_hit;

typedef struct s_col_params
{
	uint32_t	height;
	uint32_t	draw_start;
	uint32_t	draw_end;
	uint32_t	line_height;
	uint32_t	tick;
	char		reserved[4];
	t_vec2f		cam_pos;
	t_ray		*ray;
	t_hit		*hit;
	t_image		*tex;
}	t_col_params;

void		draw_border(t_image *f, uint32_t cx, uint32_t cy, float half_fov);

void		draw_minimap(t_image *f, const t_world *w, const t_assets *a);

void		init_ray(t_ray *ray, const t_player p, uint32_t width);
int			cast_ray(t_ray *ray, t_hit *hit, t_render_task *task);

uint32_t	apply_fog(uint32_t color, float distance);

void		draw_ceiling(t_image *f, t_col_params p, uint32_t x,
				const t_assets *a);
void		draw_floor(t_image *f, t_col_params p, uint32_t x,
				const t_assets *a);
void		draw_wall(t_image *f, t_col_params p, uint32_t x,
				const t_tile *tile);
t_dir		ray_to_dir(t_ray *ray, int side);

void		draw_column(t_render_task *task, t_ray *ray, t_hit *hit);

void		debug_print_fps(long now);

#endif
