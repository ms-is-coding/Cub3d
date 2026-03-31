/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_border.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:31:42 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 21:34:22 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>

#include "gfx/gfx.h"
#include "utils/vectors.h"

#include "renderer_internal.h"

static void	draw_border_line(t_image *f, uint32_t cx, uint32_t cy, float angle)
{
	int32_t	i;

	i = 0;
	while (i++ < MM_SIZE / 2)
		set_pixel((uint32_t)((int32_t)cx + (int32_t)((float)i * cosf(angle))),
			(uint32_t)((int32_t)cy + (int32_t)((float)i * sinf(angle))),
			MM_BORDER, f);
}

static void	draw_border_arc(t_image *f, uint32_t cx,
		uint32_t cy, float half_fov)
{
	const int32_t	r = MM_SIZE / 2 - 1;
	float			angle;
	int32_t			dr;
	float			rf;

	dr = -2;
	while (++dr <= 1)
	{
		rf = (float)(r + dr);
		angle = -M_PI_2f - half_fov;
		while (angle < -M_PI_2f + half_fov)
		{
			set_pixel((uint32_t)((int32_t)cx + (int32_t)(rf * cosf(angle))),
				(uint32_t)((int32_t)cy + (int32_t)(rf * sinf(angle))),
				MM_BORDER, f);
			angle += 1.0f / rf;
		}
	}
}

void	draw_border(t_image *f, uint32_t cx, uint32_t cy, float half_fov)
{
	draw_border_arc(f, cx, cy, half_fov);
	draw_border_line(f, cx, cy, -M_PI_2f - half_fov);
	draw_border_line(f, cx, cy, -M_PI_2f + half_fov);
}
