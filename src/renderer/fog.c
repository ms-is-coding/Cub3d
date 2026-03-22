/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:58 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/21 17:05:56 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "common.h"
#include "gfx/gfx.h"

#include "renderer_internal.h"

uint32_t	apply_fog(uint32_t color, float distance)
{
	float		fog_factor;

	if (distance <= FOG_START)
		return (color);
	if (distance >= FOG_END)
		return (FOG_COLOR);
	fog_factor = (distance - FOG_START) / (FOG_END - FOG_START);
	return (blend_colors(color, FOG_COLOR, fog_factor));
}
