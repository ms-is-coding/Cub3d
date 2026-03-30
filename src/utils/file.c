/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:02:33 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 19:44:15 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "error.h"

#include "file.h"

bool	is_valid_name(const char *path)
{
	size_t		len;
	const char	*dot;

	if (!path || !*path)
		return (false);
	len = ft_strlen(path);
	if (len < 5)
		return (false);
	dot = path + len - 4;
	if (ft_strncmp(dot, ".cub\0", 4) != 0)
		return (false);
	return (true);
}

void	unmap_file(t_file *file)
{
	if (!file || !file->data || file->size <= 0)
		return ;
	munmap((void *)(size_t)file->data, file->size);
	ft_memset(file, 0, sizeof(t_file));
}

int	map_file(t_file *file, const char *path)
{
	struct stat	st;
	int			fd;

	if (!file)
		return (print_error(MOD_UTILS, ERR_NULL_PTR, 1));
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (print_error(MOD_UTILS, ERR_PERROR, 1));
	}
	fstat(fd, &st);
	if (st.st_size <= 0)
	{
		close(fd);
		return (print_error(MOD_UTILS, ERR_PERROR, 1));
	}
	file->data = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (file->data == MAP_FAILED)
		return (print_error(MOD_UTILS, ERR_PERROR, 1));
	file->size = (size_t)st.st_size;
	return (0);
}
