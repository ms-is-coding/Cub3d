/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:01:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 15:30:15 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "gfx.h"

/**
 * @brief Sets a given color value to a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param c Color
 * @param image Image pointer
 */
void	set_pixel(uint32_t x, uint32_t y, uint32_t color, t_image *img)
{
	uint32_t	offset;

	if (!img || x >= img->width || y >= img->height)
		return ;
	if (color > 0xFFFFFF)
		color = 0xFFFFFF;
	offset = y * (img->linesz / 4) + x;
	*(img->data + offset) = color;
}

/**
 * @brief Adds a given color value to a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param c Color
 * @param img Image pointer
 */
void	add_pixel(uint32_t x, uint32_t y, unsigned int color, t_image *img)
{
	uint32_t	offset;

	if (!img || x >= img->width || y >= img->height)
		return ;
	offset = y * (img->linesz / 4) + x;
	color += *(img->data + offset);
	if (color > 0xFFFFFF)
		color = 0xFFFFFF;
	*(img->data + offset) = color;
}

/**
 * @brief Gives the given color value of a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param img Image pointer
 * @return Color value of the pixel.
 */
uint32_t	get_pixel(uint32_t x, uint32_t y, t_image *img)
{
	uint32_t	offset;

	if (!img || x >= img->width || y >= img->height)
		return (0);
	offset = y * (img->linesz / 4) + x;
	return (*(img->data + offset));
}

uint32_t	blend_colors(uint32_t src, uint32_t dst, float t)
{
	int	r;
	int	g;
	int	b;

	if (t <= 0)
		return (src);
	if (t >= 1)
		return (dst);
	r = (int)(((1 - t) * ((src >> 16) & 0xFF)) + (t * ((dst >> 16) & 0xFF)));
	g = (int)(((1 - t) * ((src >> 8) & 0xFF)) + (t * ((dst >> 8) & 0xFF)));
	b = (int)(((1 - t) * (src & 0xFF)) + (t * (dst & 0xFF)));
	return ((uint32_t)(r << 16 | g << 8 | b));
}
