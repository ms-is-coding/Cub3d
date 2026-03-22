/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:54:41 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:32:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

#include "utils/error.h"

#include "parser_internal.h"

static bool	is_tile_player(t_assets *a, size_t pos)
{
	return (a->tiles[a->map.data[pos]].flags & TILE_F_PLAYER);
}

static bool	is_tile_valid(t_assets *a, size_t i)
{
	size_t	x;
	size_t	y;

	x = i % a->map.width;
	y = i / a->map.width;
	return (!(a->tiles[a->map.data[i]].flags & TILE_F_WALKABLE)
		|| (x != 0 && x != a->map.width - 1 && y != 0 && y != a->map.height - 1
			&& !(a->tiles[a->map.data[i - 1]].flags & TILE_F_VOID)
			&& !(a->tiles[a->map.data[i + 1]].flags & TILE_F_VOID)
			&& !(a->tiles[a->map.data[i - a->map.width]].flags & TILE_F_VOID)
			&& !(a->tiles[a->map.data[i + a->map.width]].flags & TILE_F_VOID)));
}

int	validate_map(t_assets *a)
{
	size_t	i;
	bool	player_found;

	i = 0;
	player_found = false;
	while (i < a->map.width * a->map.height)
	{
		if (is_tile_player(a, i))
		{
			if (player_found)
				return (print_error(MOD_PARSER, ERR_MAP_TOO_MANY_PLAYERS, 1));
			a->map.player_pos = i;
			player_found = true;
		}
		if (!is_tile_valid(a, i))
			return (print_error(MOD_PARSER, ERR_MAP_BAD_SURROUND, 1));
		i++;
	}
	if (!player_found)
		return (print_error(MOD_PARSER, ERR_TILE_NO_PLAYER, 1));
	return (0);
}
