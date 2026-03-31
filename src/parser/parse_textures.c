/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:30:34 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/31 14:57:45 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utils/t_str.h"
#include "utils/error.h"
#include "../../lib/libft/libft.h"
#include "parser_internal.h"

#include <stdio.h>

#define PATH_SIZE 256

const t_str	g_tex_keys[] = {
[TEX_INVALID] = {"invalid", 7},
[TEX_SKYBOX] = {"skybox", 6},
[TEX_FLOOR] = {"floor", 5},
[TEX_CEILING] = {"ceiling", 7},
{NULL, 0}
};

static int	extract_frame_count(t_str *str, uint32_t *value)
{
	t_str		prefix;
	t_str		count_str;
	size_t		i;
	size_t		len;

	len = str->len;
	i = 0;
	while (i < len && str->ptr[i] != ',')
		i++;
	if (i == len)
		return (0);
	prefix.ptr = str->ptr;
	prefix.len = i;
	back_trim_str(&prefix);
	count_str.ptr = str->ptr + i + 1;
	count_str.len = len - i - 1;
	front_trim_str(&count_str);
	back_trim_str(&count_str);
	*str = prefix;
	if (!parse_uint32_str(count_str, value))
		return (-1);
	return (1);
}

static bool	parse_tile_texture_meta(t_str *key, t_str *option,
	uint32_t *frame_count)
{
	int	key_status;
	int	option_status;

	*frame_count = 1;
	key_status = extract_frame_count(key, frame_count);
	if (key_status < 0)
		return (false);
	option_status = extract_frame_count(option, frame_count);
	if (option_status < 0 || (key_status > 0 && option_status > 0))
		return (false);
	if (key->len != 1)
		return (false);
	if (*frame_count == 0 || *frame_count > 128)
		return (false);
	return (true);
}

static int	add_tile_texture(t_assets *a, t_str key, t_str option, t_str path)
{
	char			buf[PATH_SIZE];
	t_tile			*tile;
	uint32_t		dir;
	uint32_t		frame_count;

	tile = &a->tiles[(unsigned char)key.ptr[0] - 32];
	if (!tile->flags)
		return (print_error(MOD_PARSER, ERR_TILE_NO_FLAG, 1));
	if (!parse_tile_texture_meta(&key, &option, &frame_count))
		return (print_error(MOD_PARSER, ERR_TEX_INVALID_FRAME_COUNT, 1));
	dir = parse_dir_option(option);
	if (dir >= DIR_COUNT || dir == DIR_INVALID)
		return (print_error(MOD_PARSER, ERR_TEX_INVALID_DIR, 1));
	if (tile->textures[dir] != NULL)
		return (print_error(MOD_PARSER, ERR_TEX_DOUBLE_DEF, 1));
	if (path.len >= sizeof(buf))
		return (print_error(MOD_PARSER, ERR_TEX_PATH_TOO_LONG, 1));
	ft_memcpy(buf, path.ptr, path.len);
	buf[path.len] = '\0';
	tile->textures[dir] = get_image_from_xpm(a->gfx->mlx, buf);
	if (tile->textures[dir] == NULL)
		return (print_error(MOD_PARSER, ERR_IMG_LOAD, 1));
	tile->frame_count[dir] = frame_count;
	return (0);
}

static int	add_asset_texture(t_assets *a, t_str key, t_str option, t_str path)
{
	char	buf[PATH_SIZE];
	size_t	i;

	(void)option;
	if (key.len < 2)
		return (print_error(MOD_PARSER, ERR_TEX_INVALID_KEY, 1));
	i = TEX_INVALID;
	while (g_tex_keys[i].ptr)
	{
		if (g_tex_keys[i].len == key.len
			&& strncmp(key.ptr, g_tex_keys[i].ptr, key.len) == 0)
			break ;
		i++;
	}
	if (a->asset_tex[i] != NULL)
		return (print_error(MOD_PARSER, ERR_TEX_DOUBLE_DEF, 1));
	if (path.len >= sizeof(buf))
		return (print_error(MOD_PARSER, ERR_TEX_PATH_TOO_LONG, 1));
	ft_memcpy(buf, path.ptr, path.len);
	buf[path.len] = '\0';
	a->asset_tex[i] = get_image_from_xpm(a->gfx->mlx, buf);
	if (a->asset_tex[i] == NULL)
		return (print_error(MOD_PARSER, ERR_IMG_LOAD, 1));
	return (0);
}

int	parse_textures(t_assets *a, t_parser p)
{
	t_str		line;
	t_str		key;
	t_str		option;
	t_str		path;
	int			status;

	while (next_line(&p, &line, true, true))
	{
		if (line.len == 0)
			continue ;
		if (!split_key_value(line, &key, &path))
			return (print_error(MOD_PARSER, ERR_NO_KEYVAL, 1));
		if (key.len == 0)
			return (print_error(MOD_PARSER, ERR_TEX_NO_KEY, 1));
		if (path.len == 0)
			return (print_error(MOD_PARSER, ERR_TEX_NO_PATH, 1));
		split_key_option(key, &key, &option);
		if (is_tile_key(key))
			status = add_tile_texture(a, key, option, path);
		else
			status = add_asset_texture(a, key, option, path);
		if (status)
			return (status);
	}
	return (0);
}
