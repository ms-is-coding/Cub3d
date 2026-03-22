/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:41:09 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:22:25 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils/t_str.h"
#include "utils/utils.h"
#include "utils/error.h"

#include "parser_internal.h"

static int	get_map_size(t_parser p, size_t	*w, size_t *h, size_t *offset)
{
	t_str	line;
	size_t	gap;
	size_t	min_line;
	size_t	max_line;

	gap = 1;
	while (next_line(&p, &line, false, true))
	{
		max_line = line.len;
		front_trim_str(&line);
		min_line = max_line - line.len;
		if (line.len == 0)
		{
			gap += (*h != 0);
			continue ;
		}
		if (*offset > min_line)
			*offset = min_line;
		if (*w < max_line)
			*w = max_line;
		*h += gap;
		gap = 1;
	}
	*w -= *offset;
	return (*h == 0 || *w == 0);
}

static int	populate_map(t_assets *a, t_parser p, size_t offset)
{
	t_str		line;
	size_t		x;
	size_t		y;
	char		tile;

	y = 0;
	while (next_line(&p, &line, false, true))
	{
		if (line.len == 0 && y == 0)
			continue ;
		offset_str(&line, offset);
		x = 0;
		while (x < a->map.width)
		{	
			tile = (x < line.len) * line.ptr[x] + (x >= line.len) * ' ';
			if (!is_printable(tile))
				return (print_error(MOD_PARSER, ERR_MAP_NON_PRINTABLE_TILE, 1));
			if (a->tiles[(uint32_t)tile - 32].flags == TILE_F_NONE)
				return (print_error(MOD_PARSER, ERR_MAP_NO_TILE, 1));
			a->map.data[y * a->map.width + x] = (uint8_t)tile - 32;
			x++;
		}
		y++;
	}
	return (0);
}

int	parse_map(t_assets *a, t_parser p)
{
	size_t	offset;

	a->map.width = 0;
	a->map.height = 0;
	offset = SIZE_MAX;
	if (get_map_size(p, &a->map.width, &a->map.height, &offset))
		return (print_error(MOD_PARSER, ERR_MAP_SIZE_INVALID, 1));
	a->map.data = malloc(sizeof(uint8_t) * (a->map.width * a->map.height));
	if (!a->map.data)
		return (1);
	if (populate_map(a, p, offset))
	{
		free(a->map.data);
		a->map.data = NULL;
		return (1);
	}
	return (0);
}
