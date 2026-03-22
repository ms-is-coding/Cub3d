/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:56:11 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:24:43 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "utils/t_str.h"

#include "parser_internal.h"

static int	parse_u8(t_str *s, unsigned char *out)
{
	uint32_t	val;
	size_t		i;

	val = 0;
	i = 0;
	while (i < s->len && (s->ptr[i] >= '0' && s->ptr[i] <= '9'))
	{
		val = val * 10 + (uint32_t)(s->ptr[i] - '0');
		if (val > 255)
			return (1);
		i++;
	}
	if (i == 0)
		return (1);
	s->ptr += i;
	s->len -= i;
	*out = (unsigned char)val;
	return (0);
}

static int	skip_comma(t_str *line)
{
	if (line->len == 0 || *line->ptr != ',')
		return (1);
	line->ptr++;
	line->len--;
	return (0);
}

uint32_t	parse_rgb(t_str value)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	front_trim_str(&value);
	if (parse_u8(&value, &r))
		return (RGB_ERROR);
	front_trim_str(&value);
	if (skip_comma(&value))
		return (RGB_ERROR);
	front_trim_str(&value);
	if (parse_u8(&value, &g))
		return (RGB_ERROR);
	front_trim_str(&value);
	if (skip_comma(&value))
		return (RGB_ERROR);
	front_trim_str(&value);
	if (parse_u8(&value, &b))
		return (RGB_ERROR);
	front_trim_str(&value);
	if (value.len != 0)
		return (RGB_ERROR);
	return ((uint32_t)(r << 16 | g << 8 | b));
}
