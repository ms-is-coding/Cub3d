/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:31:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/30 19:59:44 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "assets/assets.h"
#include "utils/t_str.h"
#include "utils/error.h"
#include "../../lib/libft/libft.h"
#include "parser_internal.h"

static uint32_t	parse_tile_flags(t_str value)
{
	if (value.len == 4 && !ft_strncmp(value.ptr, "wall", 4))
		return (TILE_F_WALL);
	if (value.len == 6 && !ft_strncmp(value.ptr, "player", 6))
		return (TILE_F_PLAYER | TILE_F_WALKABLE);
	if (value.len == 4 && !ft_strncmp(value.ptr, "door", 4))
		return (TILE_F_DOOR | TILE_F_RAY_BLOCK);
	if (value.len == 5 && !ft_strncmp(value.ptr, "floor", 5))
		return (TILE_F_WALKABLE);
	return (TILE_F_NONE);
}

static bool	add_tile(t_assets *assets, char id, t_tile_flags flags)
{
	t_tile	*tile;

	if (assets->tiles[(unsigned char)id - 32].flags)
		return (false);
	tile = &assets->tiles[(unsigned char)id - 32];
	tile->flags = (t_tile_flags)flags;
	return (true);
}

int	parse_tiles(t_assets *a, t_parser p)
{
	t_str			line;
	t_str			key;
	t_str			value;
	t_tile_flags	flags;

	while (next_line(&p, &line, true, true))
	{
		if (line.len == 0)
			continue ;
		if (!split_key_value(line, &key, &value))
			return (print_error(MOD_PARSER, ERR_NO_KEYVAL, 1));
		if (!is_tile_key(key))
			return (print_error(MOD_PARSER, ERR_TILE_INVALID_KEY, 1));
		if (value.len == 0)
			return (print_error(MOD_PARSER, ERR_TILE_NO_FLAG, 1));
		flags = parse_tile_flags(value);
		if (flags == TILE_F_NONE)
			return (print_error(MOD_PARSER, ERR_TILE_UNKNOWN_FLAG, 1));
		if (!add_tile(a, key.ptr[0], flags))
			return (print_error(MOD_PARSER, ERR_TILE_DOUBLE_DEF, 1));
	}
	if (!add_tile(a, ' ', TILE_F_VOID))
		return (print_error(MOD_PARSER, ERR_TILE_DOUBLE_DEF, 1));
	return (0);
}
