/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:36:02 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 11:38:12 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include <stddef.h>

typedef struct s_file {
	const char		*path;
	const char		*data;
	size_t			size;
}	t_file;

bool	is_valid_name(const char *path);

void	unmap_file(t_file *file);
t_file	map_file(const char *path);

#endif
