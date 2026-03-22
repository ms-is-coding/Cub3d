/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:55:10 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 10:58:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdint.h>

typedef union u_vec2i {
	struct {
		int32_t	x;
		int32_t	y;
	};
	int32_t	e[2];
}	t_vec2i;

typedef union u_vec3i {
	struct {
		int32_t	x;
		int32_t	y;
		int32_t	z;
	};
	int32_t	e[3];
}	t_vec3i;

typedef union u_vec2u {
	struct {
		uint32_t	x;
		uint32_t	y;
	};
	uint32_t	e[2];
}	t_vec2u;

typedef union u_vec3u {
	struct {
		uint32_t	x;
		uint32_t	y;
		uint32_t	z;
	};
	uint32_t	e[3];
}	t_vec3u;

typedef union u_vec2f {
	struct {
		float	x;
		float	y;
	};
	float	e[2];
}	t_vec2f;

typedef union u_vec3f {
	struct {
		float	x;
		float	y;
		float	z;
	};
	float	e[3];
}	t_vec3f;

#endif
