/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:52:57 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/30 21:18:22 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include <stddef.h>
# include <stdbool.h>

# include "utils/t_str.h"

# include "assets/assets.h"

typedef struct s_parser
{
	const char		*cur;
	const char		*end;
}	t_parser;

typedef int	(*t_parse_fn)(t_assets *, t_parser);
typedef int	(*t_validate_fn)(t_assets *);

typedef struct s_section_fns
{
	t_parse_fn		parse;
	t_validate_fn	validate;
}	t_section_fns;

typedef struct s_section
{
	const char		*name;
	size_t			len;
	t_parse_fn		parse;
	t_validate_fn	validate;
	char			flag;

	char			reserved[7];
}	t_section;

bool		next_line(t_parser *p, t_str *line, bool front, bool back);
uint32_t	parse_dir_option(t_str option);
bool		is_tile_key(t_str key);
bool		parse_uint32_str(t_str str, uint32_t *value);

uint32_t	parse_rgb(t_str value);

int			parse_tiles(t_assets *a, t_parser p);
int			parse_textures(t_assets *a, t_parser p);
int			parse_colors(t_assets *a, t_parser p);
int			parse_map(t_assets *a, t_parser p);

int			validate_tiles(t_assets *a);
int			validate_textures(t_assets *a);
int			validate_colors(t_assets *a);
int			validate_map(t_assets *a);

#endif
