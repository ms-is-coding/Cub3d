/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:25:04 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/21 20:44:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "parser/parser.h"
#include "utils/file.h"
#include "utils/error.h"

#include "assets.h"

static void	assets_colors_init(t_assets *a)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 95)
	{
		j = 0;
		while (j < DIR_COUNT)
		{
			a->tiles[i].colors[j] = RGB_INVALID;
			j++;
		}
		i++;
	}
	a->ceiling = RGB_INVALID;
	a->floor = RGB_INVALID;
}

int	assets_init(t_assets *assets, const char *file_path)
{
	t_file	file;

	if (!assets || !file_path)
		return (print_error(MOD_ASSETS, ERR_NULL_PTR, 1));
	if (!is_valid_name(file_path))
		return (print_error(MOD_ASSETS, ERR_BAD_NAME, 1));
	if (map_file(&file, file_path))
		return (1);
	assets_colors_init(assets);
	if (parse_assets(assets, file.data, file.size))
	{
		assets_deinit(assets);
		unmap_file(&file);
		return (1);
	}
	unmap_file(&file);
	return (0);
}
