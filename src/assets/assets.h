/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:26:08 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 15:00:06 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# include "../gfx/gfx.h"

# define RGB_ERROR		UINT32_MAX
# define RGB_INVALID	0xFF00FF

typedef enum e_tile_flags
{
	TILE_F_NONE			= 0,
	TILE_F_VOID			= 1 << 0,
	TILE_F_SOLID		= 1 << 1,
	TILE_F_WALKABLE		= 1 << 2,
	TILE_F_RAY_BLOCK	= 1 << 3,
	TILE_F_PLAYER		= 1 << 4,
	TILE_F_ENTITY		= 1 << 6,
	TILE_F_WALL			= TILE_F_SOLID | TILE_F_RAY_BLOCK,
	TILE_F_DOOR			= TILE_F_WALL | TILE_F_ENTITY,
}	t_tile_flags;

typedef enum e_dir
{
	DIR_INVALID = 0,
	DIR_DEFAULT,
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_COUNT,
}	t_dir;

typedef enum e_asset_tex
{
	TEX_INVALID,
	TEX_SKYBOX,
	TEX_FLOOR,
	TEX_CEILING,
	TEX_COUNT,
}	t_asset_tex;

typedef struct s_tile
{
	t_tile_flags	flags;
	char			reserved[4];

	t_image			*textures[DIR_COUNT];
	uint32_t		colors[DIR_COUNT];
	uint32_t		frame_count[DIR_COUNT];

}	t_tile;

typedef enum e_col_type
{
	COL_FLOOR,
	COL_CEILING,
	COL_UNKNOWN,
}	t_col_type;

typedef struct s_map
{
	uint8_t		*data;
	size_t		width;
	size_t		height;
	size_t		player_pos;
}	t_map;

typedef struct s_assets
{
	t_map		map;

	t_tile		tiles[96];

	t_image		*asset_tex[TEX_COUNT];

	uint32_t	floor;
	uint32_t	ceiling;

	t_gfx		*gfx;
}	t_assets;

int		assets_init(t_assets *assets, const char *file_path);
void	assets_deinit(t_assets *assets);

t_tile	*map_tile_at(t_assets *assets, size_t x, size_t y);

void	debug_print_assets(t_assets *a);

#endif
