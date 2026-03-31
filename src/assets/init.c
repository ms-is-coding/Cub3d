/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:25:04 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 14:50:28 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "parser/parser.h"
#include "utils/file.h"
#include "utils/error.h"

#include "assets.h"

static void	assets_tiles_init(t_assets *a)
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
			a->tiles[i].frame_count[j] = 1;
			j++;
		}
		i++;
	}
	i = TEX_INVALID;
	while (i < TEX_COUNT)
		a->asset_tex[i++] = NULL;
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
	assets_tiles_init(assets);
	if (parse_assets(assets, file.data, file.size))
	{
		assets_deinit(assets);
		unmap_file(&file);
		return (1);
	}
	unmap_file(&file);
	return (0);
}
