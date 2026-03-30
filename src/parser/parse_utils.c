/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:47:06 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/30 21:18:30 by macarnie         ###   ########.fr       */
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
	return (key.len >= 1 && (key.len == 1 || key.ptr[1] == ',')
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

bool	parse_uint32_str(t_str str, uint32_t *value)
{
	uint32_t	result;
	uint32_t	digit;
	size_t		i;

	front_trim_str(&str);
	back_trim_str(&str);
	if (str.len == 0)
		return (false);
	result = 0;
	i = 0;
	while (i < str.len)
	{
		if (str.ptr[i] < '0' || str.ptr[i] > '9')
			return (false);
		digit = (uint32_t)(str.ptr[i] - '0');
		if (result > (UINT32_MAX - digit) / 10)
			return (false);
		result = result * 10 + digit;
		i++;
	}
	*value = result;
	return (true);
}
