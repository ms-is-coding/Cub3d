/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:15:09 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/22 11:21:25 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "utils.h"

#include "t_str.h"

size_t	front_trim_str(t_str *str)
{
	size_t	i;

	i = 0;
	while (str->len && is_whitespace(*str->ptr))
	{
		str->ptr++;
		str->len--;
		i++;
	}
	return (i);
}

size_t	back_trim_str(t_str *str)
{
	size_t	i;

	i = 0;
	while (str->len && is_whitespace(str->ptr[str->len - 1]))
		str->len--;
	return (i);
}

void	offset_str(t_str *str, size_t offset)
{
	if (offset > str->len)
		offset = str->len;
	str->ptr += offset;
	str->len -= offset;
}

bool	split_key_value(t_str entry, t_str *key, t_str *value)
{
	size_t	i;

	i = 0;
	while (i < entry.len && entry.ptr[i] != '=')
		i++;
	if (i >= entry.len || i == 0)
		return (false);
	key->ptr = entry.ptr;
	key->len = i;
	while (key->len > 0 && is_whitespace(key->ptr[key->len - 1]))
		key->len--;
	value->ptr = entry.ptr + i + 1;
	value->len = entry.len - i - 1;
	while (value->len > 0 && is_whitespace(value->ptr[0]))
	{
		value->ptr++;
		value->len--;
	}
	return (true);
}

bool	split_key_option(t_str entry, t_str *key, t_str *option)
{
	size_t	i;

	i = 0;
	while (i < entry.len && entry.ptr[i] != ':')
		i++;
	if (i >= entry.len || i == 0)
	{
		*option = (t_str){NULL, 0};
		return (false);
	}
	key->ptr = entry.ptr;
	key->len = i;
	while (key->len > 0 && is_whitespace(key->ptr[key->len - 1]))
		key->len--;
	option->ptr = entry.ptr + i + 1;
	option->len = entry.len - i - 1;
	while (option->len > 0 && is_whitespace(option->ptr[0]))
	{
		option->ptr++;
		option->len--;
	}
	return (true);
}
