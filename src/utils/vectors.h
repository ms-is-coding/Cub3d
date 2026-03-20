/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:55:10 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/18 20:09:02 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdint.h>

typedef struct s_vec2i {
	int32_t	x;
	int32_t	y;
}	t_vec2i;

typedef struct s_vec3i {
	int32_t	x;
	int32_t	y;
	int32_t	z;
}	t_vec3i;

typedef struct s_vec2u {
	uint32_t	x;
	uint32_t	y;
}	t_vec2u;

typedef struct s_vec3u {
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
}	t_vec3u;

typedef struct s_vec2f {
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}	t_vec3f;

#endif
