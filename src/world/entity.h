/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:05:44 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/27 19:57:13 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "utils/vectors.h"

typedef enum e_entity_type {
	ENTITY_NONE,
	ENTITY_DOOR,
	ENTITY_UNKNOWN,
}	t_entity_type;

typedef enum e_door_state {
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING,
}	t_door_state;

typedef struct s_door
{
	t_door_state	state;
	float			offset;
}	t_door;

typedef struct __attribute__((aligned(8))) s_player
{
	t_vec2f	pos;
	t_vec2f	vel;
	float	width;
	float	height;
	float	yaw;
	float	yaw_vel;
	float	fov;
	char	reserved[4];
}	t_player;

typedef struct __attribute__((aligned(4))) s_entity
{
	t_entity_type	type;
	t_vec2f			pos;

	union {
		t_door	door;
	};
}	t_entity;

#endif
