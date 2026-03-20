/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:37:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/20 17:17:14 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

#include <stdbool.h>
#include <stdint.h>

typedef union u_keys {
	struct s_values {
		bool	forward : 1;
		bool	backward : 1;
		bool	left : 1;
		bool	right : 1;
		bool	up : 1;
		bool	down : 1;
		bool	yaw_left : 1;
		bool	yaw_right : 1;
		bool	pitch_up : 1;
		bool	pitch_down : 1;

		int32_t	reserved : 22;
	}	values;
	uint32_t	bits;
}	t_keys;

typedef struct s_mouse {
    int32_t		last_x;
    int32_t		last_y;
    int32_t		delta_x;
    int32_t		delta_y;
    uint8_t		left_pressed;
    uint8_t		right_pressed;
    uint8_t		middle_pressed;

	char 		reserved[1];
}	t_mouse;

typedef struct s_input {
	t_keys	keys;
	t_mouse	mouse;
}	t_input;

typedef struct s_engine t_engine;

int	hooks_init(t_engine *engine);

#endif
