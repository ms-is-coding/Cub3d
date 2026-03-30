/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:05:30 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/30 21:28:58 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

#include "error.h"

#define MSG_LIMIT			126

#define MSG_USAGE			"Usage: <./cub3D filename.cub> [OPTIONS]"
#define MSG_HELP			"For help, run: <./cub3D --help>"

const char	*g_module_names[] = {
[MOD_NONE] = "None",
[MOD_OPTIONS] = "Options: ",
[MOD_GFX] = "Graphics: ",
[MOD_ASSETS] = "Assets: ",
[MOD_PARSER] = "Parser: ",
[MOD_HOOKS] = "Hooks: ",
[MOD_WORLD] = "World: ",
[MOD_PHYSICS] = "Physics: ",
[MOD_RENDERER] = "Renderer: ",
[MOD_THREADS] = "Threads: ",
[MOD_UTILS] = "Utils",
[MOD_UNKNOWN] = "Unknown module",
};

const char	*g_error_messages[] = {
[ERR_NONE] = "success",
[ERR_NO_MAP_FILE] = "no map file given. "MSG_USAGE,
[ERR_TOO_MANY_MAP_FILES] = "too many map files given. "MSG_USAGE,
[ERR_UNKNOWN_OPT] = "unknown option. "MSG_HELP,
[ERR_UNKNOWN_OPT_VALUE] = "unknown option value. "MSG_HELP,
[ERR_BAD_OPT_VALUE] = "bad option value. "MSG_HELP,
[ERR_NULL_PTR] = "unexpected null pointer(s)",
[ERR_BAD_NAME] = "invalid name "MSG_USAGE,
[ERR_UNKNOWN_SECTION] = "unknown section in map file",
[ERR_SECTION_DOUBLE_DEF] = "section defined twice in map file",
[ERR_MISSING_SECTION] = "missing section(s) in map file",
[ERR_NO_KEYVAL] = "could not get key-value pair in map file",
[ERR_MLX] = "could not initialize mlx",
[ERR_WIN] = "could not create window",
[ERR_IMG_LOAD] = "could not load image",
[ERR_IMG_CREATE] = "could not create image",
[ERR_HOOKS] = "could not set hooks",
[ERR_ENTITY_LIMIT] = "too many entities in map",
[WARN_NO_MULTITHREADING] = "multithreading not available",
[WARN_UNKNOWN_ENTITY] = "unknown entity type in map file",
[ERR_TILE_DOUBLE_DEF] = "tile defined twice in map file",
[ERR_TILE_UNKNOWN_FLAG] = "unknown tile flag specified in map file",
[ERR_TILE_NO_FLAG] = "no flags specified for tile in map file",
[ERR_TILE_INVALID_KEY] = "invalid tile key specified in map file",
[ERR_TILE_NO_PLAYER] = "no player tile defined in map file",
[ERR_TILE_NO_WALL] = "no wall tile defined in map file",
[ERR_TEX_NO_KEY] = "texture key missing in map file",
[ERR_TEX_NO_PATH] = "texture path missing in map file",
[ERR_TEX_PATH_TOO_LONG] = "texture path too long in map file",
[ERR_TEX_DOUBLE_DEF] = "texture defined twice in map file",
[ERR_TEX_NO_ADDR] = "no corresponding address to store texture in map file",
[ERR_TEX_INVALID_KEY] = "invalid texture key specified in map file",
[ERR_TEX_INVALID_DIR] = "invalid texture direction specified in map file",
[ERR_TEX_INVALID_FRAME_COUNT] = "invalid texture frame count in map file",
[ERR_TEX_NO_TILE] = "no tile defined for texture in map file",
[ERR_TEX_NO_INVALID] = "no 'invalid' texture defined in map file",
[WARN_TEX_NO_DIR] = "ray-blocking tile is missing directional texture(s)",
[ERR_COL_NO_KEY] = "color key missing in map file",
[ERR_COL_NO_PATH] = "color path missing in map file",
[ERR_COL_STR_INVALID] = "invalid color parameters specified in map file",
[ERR_COL_DOUBLE_DEF] = "color defined twice in map file",
[ERR_COL_NO_ADDR] = "no corresponding address to store color in map file",
[ERR_COL_INVALID_KEY] = "invalid key specified in map file",
[ERR_COL_INVALID_DIR] = "invalid direction specified in map file",
[ERR_COL_NO_TILE] = "no tile defined for color in map file",
[WARN_COL_NO_DIR] = "ray-blocking tile is missing directional color(s)",
[WARN_COL_NO_CEILING] = "ceiling color not set",
[WARN_COL_NO_FLOOR] = "floor color not set",
[ERR_MAP_SIZE_INVALID] = "invalid map size",
[ERR_MAP_NO_TILE] = "no tile defined for character in map",
[ERR_MAP_NON_PRINTABLE_TILE] = "non-printable character found in map",
[ERR_MAP_NO_PLAYER] = "no player starting position found in map",
[ERR_MAP_TOO_MANY_PLAYERS] = "multiple player starting positions found in map",
[ERR_MAP_BAD_SURROUND] = "map not surrounded by walls",
[ERR_PERROR] = "system error",
[ERR_UNKNOWN] = "unknown error",
};

static size_t	get_module_name(char *buf, size_t pos, t_module mod)
{
	size_t	i;

	if (mod < MOD_NONE || mod > MOD_UNKNOWN)
		mod = MOD_UNKNOWN;
	i = pos;
	if (mod != MOD_NONE)
		i += ft_strlcpy(&buf[i], g_module_names[mod], MSG_LIMIT - i);
	buf[i] = '\0';
	return (i);
}

static size_t	get_message(char *buf, size_t pos, t_module mod, t_error err)
{
	const char	*msg;
	size_t		i;

	i = get_module_name(buf, pos, mod);
	if (err < ERR_NONE || err > ERR_UNKNOWN)
		err = ERR_UNKNOWN;
	msg = g_error_messages[err];
	if (!msg)
		msg = g_error_messages[ERR_UNKNOWN];
	i += ft_strlcpy(&buf[i], msg, MSG_LIMIT - i);
	buf[i++] = '\n';
	buf[i] = '\0';
	return (i);
}

int	print_warning(t_module mod, t_error err, int int_code)
{
	char	msg[MSG_LIMIT + 2];
	size_t	i;

	if (err == ERR_NONE)
		return (int_code);
	i = ft_strlcpy(msg, "Warning\n", 9);
	i = get_message(msg, i, mod, err);
	(void)write(1, msg, i);
	return (int_code);
}

int	print_error(t_module mod, t_error err, int int_code)
{
	char	msg[MSG_LIMIT + 2];
	size_t	i;

	if (err == ERR_NONE)
		return (int_code);
	i = ft_strlcpy(msg, "Error\n", 7);
	if (err == ERR_PERROR)
	{
		get_module_name(msg, i, mod);
		perror(msg);
	}
	else
	{
		i = get_message(msg, i, mod, err);
		(void)write(2, msg, i);
	}
	return (int_code);
}
