/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:11:52 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 11:25:51 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STR_H
# define T_STR_H

# include <stddef.h>

typedef struct s_str
{
	const char	*ptr;
	size_t		len;
}	t_str;

# define T_STR_EMPTY ((t_str){NULL, 0})

size_t	front_trim_str(t_str *str);
size_t	back_trim_str(t_str *str);
bool	split_key_value(t_str entry, t_str *key, t_str *value);
bool	split_key_option(t_str entry, t_str *key, t_str *option);

#endif
