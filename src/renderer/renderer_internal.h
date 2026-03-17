/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:38:53 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/16 12:42:20 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_INTERNAL_H
# define RENDERER_INTERNAL_H

# include <stdint.h>

#include "utils/vectors.h"

typedef struct s_algo
{
	float	delta_x;
	float	delta_y;
	float	side_x;
	float	side_y;
	int		step_x;
	int		step_y;
}	t_algo;

typedef struct s_ray
{
	t_vec2f		dir;
	int			pos_x;
	int			pos_y;
	float		dist;
	uint32_t	line_height;
	int			side;
	t_algo		dda;
	uint32_t	start;
	uint32_t	end;
}	t_ray;

#endif
