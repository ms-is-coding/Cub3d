/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 03:25:02 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 10:58:10 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <sys/errno.h>
# include <stddef.h>

typedef enum e_module
{
	MOD_NONE,
	MOD_OPTIONS,
	MOD_GFX,
	MOD_ASSETS,
	MOD_PARSER,
	MOD_HOOKS,
	MOD_WORLD,
	MOD_PHYSICS,
	MOD_RENDERER,
	MOD_THREADS,
	MOD_UTILS,
	MOD_UNKNOWN,
}	t_module;

typedef enum e_error
{
	ERR_NONE,
	ERR_NO_MAP_FILE,
	ERR_TOO_MANY_MAP_FILES,
	ERR_UNKNOWN_OPT,
	ERR_UNKNOWN_OPT_VALUE,
	ERR_BAD_OPT_VALUE,
	ERR_NULL_PTR,
	ERR_BAD_NAME,
	ERR_UNKNOWN_SECTION,
	ERR_SECTION_DOUBLE_DEF,
	ERR_MISSING_SECTION,
	ERR_NO_KEYVAL,
	ERR_MLX,
	ERR_WIN,
	ERR_IMG_LOAD,
	ERR_IMG_CREATE,
	ERR_HOOKS,
	WARN_NO_MULTITHREADING,
	ERR_TILE_DOUBLE_DEF,
	ERR_TILE_UNKNOWN_FLAG,
	ERR_TILE_NO_FLAG,
	ERR_TILE_INVALID_KEY,
	ERR_TILE_NO_PLAYER,
	ERR_TILE_NO_WALL,
	ERR_TEX_NO_KEY,
	ERR_TEX_NO_PATH,
	ERR_TEX_PATH_TOO_LONG,
	ERR_TEX_DOUBLE_DEF,
	ERR_TEX_NO_ADDR,
	ERR_TEX_INVALID_KEY,
	ERR_TEX_INVALID_DIR,
	ERR_TEX_NO_TILE,
	ERR_TEX_NO_INVALID,
	WARN_TEX_NO_DIR,
	ERR_COL_NO_KEY,
	ERR_COL_NO_PATH,
	ERR_COL_STR_INVALID,
	ERR_COL_DOUBLE_DEF,
	ERR_COL_NO_ADDR,
	ERR_COL_INVALID_KEY,
	ERR_COL_INVALID_DIR,
	ERR_COL_NO_TILE,
	WARN_COL_NO_DIR,
	WARN_COL_NO_CEILING,
	WARN_COL_NO_FLOOR,
	ERR_MAP_SIZE_INVALID,
	ERR_MAP_NO_TILE,
	ERR_MAP_NON_PRINTABLE_TILE,
	ERR_MAP_NO_PLAYER,
	ERR_MAP_TOO_MANY_PLAYERS,
	ERR_MAP_BAD_SURROUND,
	ERR_PERROR,
	ERR_UNKNOWN,
}	t_error;

int	print_warning(t_module mod, t_error err, int int_code);
int	print_error(t_module mod, t_error err, int int_code);

#endif
