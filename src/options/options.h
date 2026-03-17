/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:37:42 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/26 19:33:30 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_options {
	uint32_t		width;
	uint32_t		height;
	int16_t			thread_count;
	int16_t			fps;

}	t_options;

typedef struct s_option {
	const char *const	name;
	const char *const	short_name;
	size_t				offset;
	int64_t				min;
	int64_t				max;
	int					(*parse)(t_options *opts, struct s_option opt,
			const char *const str);
}	t_option;

typedef int		(*t_opt_parse_fn)(t_options *opts, t_option opt,
			const char *const str);

int	options_parse_i16(t_options *opts, t_option opt, const char *const str);
int	options_parse_u32(t_options *opts, t_option opt, const char *const str);

int	options_init(t_options *opt, int argc, char **argv);

#endif
