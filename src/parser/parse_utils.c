/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:47:06 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:28:42 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "utils/t_str.h"

#include "parser_internal.h"

#include "utils/t_str.h"

bool	next_line(t_parser *p, t_str *line, bool do_front, bool do_back)
{
	const char	*start;

	if (p->cur >= p->end)
		return (false);
	start = p->cur;
	while (p->cur < p->end && *p->cur != '\n')
		p->cur++;
	line->ptr = start;
	line->len = (size_t)(p->cur - start);
	if (p->cur < p->end)
		p->cur++;
	if (do_front)
		front_trim_str(line);
	if (do_back)
		back_trim_str(line);
	return (true);
}

bool	is_tile_key(t_str key)
{
	return (key.len == 1
		&& (key.ptr[0] >= 32 && key.ptr[0] <= 126)
		&& key.ptr[0] != ' '
		&& key.ptr[0] != '='
		&& key.ptr[0] != ':'
		&& key.ptr[0] != '['
		&& key.ptr[0] != ']');
}

uint32_t	parse_dir_option(t_str option)
{
	static const t_dir	tiles['z' - 'a' + 1] = {
	['n' - 'a'] = DIR_NORTH,
	['s' - 'a'] = DIR_SOUTH,
	['w' - 'a'] = DIR_WEST,
	['e' - 'a'] = DIR_EAST,
	['d' - 'a'] = DIR_DEFAULT,
	};
	char				c;

	if (option.len == 0)
		return (DIR_DEFAULT);
	if (option.len > 1)
		return (DIR_INVALID);
	c = option.ptr[0];
	if (c >= 'A' && c <= 'Z')
		return (tiles[c - 'A']);
	if (c >= 'a' && c <= 'z')
		return (tiles[c - 'a']);
	return (DIR_INVALID);
}
