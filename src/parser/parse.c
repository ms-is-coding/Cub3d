/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:26:02 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:30:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "parser_internal.h"
#include "utils/error.h"

#include "parser.h"

enum {
	SEC_TILES = 1 << 0,
	SEC_TEXTURES = 1 << 1,
	SEC_COLORS = 1 << 2,
	SEC_MAP = 1 << 3,
	SEC_ALL = 0xf
};

t_section	g_sections[] = {
{
	.name = "TILES",
	.len = 5,
	.parse = parse_tiles,
	.validate = validate_tiles,
	.flag = SEC_TILES,
}, {
	.name = "TEXTURES",
	.len = 8,
	.parse = parse_textures,
	.validate = validate_textures,
	.flag = SEC_TEXTURES,
}, {
	.name = "COLORS",
	.len = 6,
	.parse = parse_colors,
	.validate = validate_colors,
	.flag = SEC_COLORS,
}, {
	.name = "MAP",
	.len = 3,
	.parse = parse_map,
	.validate = validate_map,
	.flag = SEC_MAP,
}
};

static bool	is_section(t_str str)
{
	return (str.len >= 3 && str.ptr[0] == '[' && str.ptr[str.len - 1] == ']');
}

static int	get_section_name(t_str *str)
{
	if (is_section(*str))
	{
		str->ptr += 1;
		str->len -= 2;
		return (0);
	}
	return (1);
}

static int	get_section_fns(t_str str, t_section_fns *f, char *found)
{
	size_t			i;
	const size_t	section_count = sizeof(g_sections) / sizeof(t_section);

	i = 0;
	while (i < section_count)
	{
		if (g_sections[i].len == str.len
			&& strncmp(str.ptr, g_sections[i].name, g_sections[i].len) == 0)
		{
			if (*found & g_sections[i].flag)
				return (print_error(MOD_PARSER, ERR_SECTION_DOUBLE_DEF, 1));
			*found |= g_sections[i].flag;
			f->parse = g_sections[i].parse;
			f->validate = g_sections[i].validate;
			break ;
		}
		i++;
	}
	if (i == section_count)
		return (print_error(MOD_PARSER, ERR_UNKNOWN_SECTION, 1));
	return (0);
}

int	parse_assets(t_assets *assets, const char *data, size_t size)
{
	t_parser		p;
	t_str			line;
	t_parser		s;
	t_section_fns	f;
	char			flags;

	flags = 0;
	p = (t_parser){data, data + size};
	while (next_line(&p, &line, true, true))
	{
		if (get_section_name(&line))
			continue ;
		if (get_section_fns(line, &f, &flags))
			return (1);
		s = (t_parser){p.cur, p.cur};
		while (next_line(&p, &line, true, true) && !is_section(line))
			s.end = p.cur;
		if (f.parse(assets, s) || f.validate(assets))
			return (1);
		if (is_section(line))
			p.cur = line.ptr;
	}
	if (SEC_ALL == (flags & SEC_ALL))
		return (0);
	return (print_error(MOD_PARSER, ERR_MISSING_SECTION, 1));
}
