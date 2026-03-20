/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:19:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/20 17:17:40 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include <pthread.h>
# include <stdatomic.h>

# include "world/world.h"
# include "hooks/hooks.h"

# define MOVE_SPEED 5.0f
# define ROT_SPEED 10.0f
# define MOUSE_SENSITIVITY 1.0f

typedef struct s_physics {
	t_world_buffer	*world_buffer;
	t_input			*input;
	pthread_t		thread;
	atomic_int		running;
	char			reserved[4];
}	t_physics;

int		physics_init(t_physics *p);
void	physics_deinit(t_physics *p);
void	physics_update(t_physics *p, float dt);

#endif
