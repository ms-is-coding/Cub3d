/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:02:33 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 11:37:14 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "file.h"

bool	is_valid_name(const char *path)
{
	const char	*find;

	if (!path || strlen(path) < 5)
		return (false);
	find = memmem(path, strlen(path) + 1, ".cub\0", 5);
	if (!find || find[-1] == '/')
		return (false);
	return (true);
}

void	unmap_file(t_file *file)
{
	if (!file || !file->data || file->size <= 0)
		return ;
	munmap((void *)file->data, file->size);
	memset(file, 0, sizeof(t_file));
}

t_file	map_file(const char *path)
{
	struct stat	st;
	t_file		file;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((t_file){.size = 0}); //do a print_error here
	fstat(fd, &st);
	if (st.st_size <= 0)
		return ((t_file){.size = 0}); //to be defined in error.h
	file.data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file.data == MAP_FAILED)
		return ((t_file){.size = 0}); //to be defined in error.h
	close(fd);
	file.size = (size_t)st.st_size;
	return (file);
}
