/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 18:38:58 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 19:42:40 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "options/options.h"

int	options_parse_i16(t_options *opts, t_option opt, const char *const str)
{
	int64_t	value;
	char	*end;

	value = strtol(str, &end, 10);
	if (value > opt.max || value < opt.min || *end != '\0')
		return (1);
	*(int16_t *)((void *)((char *)opts + opt.offset)) = (int16_t)value;
	return (0);
}

int	options_parse_i32(t_options *opts, t_option opt, const char *const str)
{
	int64_t	value;
	char	*end;

	value = strtol(str, &end, 10);
	if (value > opt.max || value < opt.min || *end != '\0')
		return (1);
	*(int32_t *)((void *)((char *)opts + opt.offset)) = (int32_t)value;
	return (0);
}
