/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:15:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 10:19:11 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "options/options.h"

int	options_parse_u32(t_options *opts, t_option opt, const char *const str)
{
	int64_t	value;
	char	*end;

	value = strtol(str, &end, 10);
	if (value > opt.max || value < opt.min || *end != '\0')
		return (1);
	*(uint32_t *)((void *)((char *)opts + opt.offset)) = (uint32_t)value;
	return (0);
}
