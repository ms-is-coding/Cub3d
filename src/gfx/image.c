/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image-temp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:02:10 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 19:32:34 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <string.h>
#include <stdlib.h>

#include "gfx.h"

void	free_image(void *mlx, t_image *img)
{
	if (!img)
		return ;
	if (mlx && img->ptr)
		mlx_destroy_image(mlx, img->ptr);
	free(img);
}

t_image	*get_image_from_xpm(void *mlx, char *file) 
{
	t_image	*img = {0};

	if (!mlx || !file)
		return (NULL);
	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(
		mlx,
		file,
		(int *)&img->width,
		(int *)&img->height
	);
	if (!img->ptr)
		return (free(img), NULL);
	img->data = (uint32_t *)(void *)mlx_get_data_addr(
		img->ptr,
		(int *)&img->bpp,
		(int *)&img->linesz,
		&(int){0}
		);
	if (!img->data)
		return (free_image(mlx, img), NULL);
	return (img);
}

int	gfx_image_create(const t_gfx *gfx, t_image *img,
		uint32_t width, uint32_t height)
{
	img->ptr = mlx_new_image(gfx->mlx, (int)width, (int)height);
	if (!img->ptr)
		return (1);
	img->data = (uint32_t *)(void *)mlx_get_data_addr(
		img->ptr,
		(int *)&img->bpp,
		(int *)&img->linesz,
		&(int){0}
		);
	img->width = width;
	img->height = height;
	return (0);
}
