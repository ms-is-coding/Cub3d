/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:29:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 15:39:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "assets/assets.h"
#include "utils/t_str.h"
#include "utils/error.h"

#include "parser_internal.h"

static int	add_tile_color(t_assets *a, t_str key, t_str option, t_str value)
{
	uint32_t	rgb;
	t_tile		*tile;
	uint32_t	dir;

	tile = &a->tiles[(unsigned char)key.ptr[0] - 32];
	if (tile->flags == TILE_F_NONE)
		return (print_error(MOD_PARSER, ERR_COL_NO_TILE, 1));
	dir = parse_dir_option(option);
	if (dir >= DIR_COUNT)
		return (print_error(MOD_PARSER, ERR_COL_INVALID_DIR, 1));
	if (tile->colors[dir] != RGB_INVALID)
		return (print_error(MOD_PARSER, ERR_COL_DOUBLE_DEF, 1));
	rgb = parse_rgb(value);
	if (rgb == RGB_ERROR)
		return (print_error(MOD_PARSER, ERR_COL_STR_INVALID, 1));
	tile->colors[dir] = rgb;
	return (0);
}

static int	add_asset_color(t_assets *a, t_str key, t_str option, t_str value)
{
	uint32_t	*color;
	uint32_t	rgb;

	(void)option;
	if (key.len < 2)
		return (print_error(MOD_PARSER, ERR_COL_INVALID_KEY, 1));
	if (key.len == 7 && strncmp(key.ptr, "ceiling", 7) == 0)
		color = &a->ceiling;
	else if (key.len == 5 && strncmp(key.ptr, "floor", 5) == 0)
		color = &a->floor;
	else
		return (print_error(MOD_PARSER, ERR_COL_NO_ADDR, 1));
	if (*color != RGB_INVALID)
		return (print_error(MOD_PARSER, ERR_COL_DOUBLE_DEF, 1));
	rgb = parse_rgb(value);
	if (rgb == RGB_ERROR)
		return (print_error(MOD_PARSER, ERR_COL_STR_INVALID, 1));
	*color = rgb;
	return (0);
}

int	parse_colors(t_assets *a, t_parser p)
{
	t_str		line;
	t_str		key;
	t_str		value;
	t_str		option;
	int			status;

	while (next_line(&p, &line, true, true))
	{
		if (line.len == 0)
			continue ;
		if (!split_key_value(line, &key, &value))
			return (print_error(MOD_PARSER, ERR_NO_KEYVAL, 1));
		if (key.len == 0)
			return (print_error(MOD_PARSER, ERR_COL_NO_KEY, 1));
		if (value.len == 0)
			return (print_error(MOD_PARSER, ERR_COL_NO_PATH, 1));
		split_key_option(key, &key, &option);
		if (is_tile_key(key))
			status = add_tile_color(a, key, option, value);
		else
			status = add_asset_color(a, key, option, value);
		if (status)
			return (status);
	}
	return (0);
}
