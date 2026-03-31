/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:15:36 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/31 20:14:40 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <inttypes.h>

#include "libft.h"

#include "options/options.h"

int	options_parse_u32(t_options *opts, t_option opt, const char *const str)
{
	int64_t	value;
	char	*end;

	value = ft_strtol(str, &end, 10);
	if (value > opt.max || value < opt.min || *end != '\0')
		return (1);
	*(uint32_t *)((void *)((char *)opts + opt.offset)) = (uint32_t)value;
	return (0);
}
