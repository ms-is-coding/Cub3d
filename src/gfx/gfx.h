/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:11:57 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 20:32:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <stdint.h>
# include "options/options.h"

typedef struct s_gfx {
	void		*mlx;
	void		*win;
}	t_gfx;

typedef struct s_image {
	void		*ptr;
	uint32_t	*data;
	uint32_t	width; // investigate the usefulness (vs linesz)
	uint32_t	height;
	uint32_t	bpp;
	uint32_t	linesz;
}	t_image;

void		set_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img);
void		add_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img);
uint32_t	get_pixel(uint32_t x, uint32_t y, t_image *img);
uint32_t	blend_colors(uint32_t src_c, uint32_t dst_c, float t);

void		gfx_image_destroy(void *mlx, t_image *img);
t_image		*get_image_from_xpm(void *mlx, char *file);
int			gfx_image_create(void *mlx, t_image *img, uint32_t w, uint32_t h);

int			gfx_init(t_gfx *gfx, const t_options *opt);
void		gfx_deinit(t_gfx *gfx);

void		gfx_present(const t_gfx *gfx, const t_image *img);
void		gfx_loop(t_gfx *gfx, int (*fn)(void), void *userdata);


#endif
