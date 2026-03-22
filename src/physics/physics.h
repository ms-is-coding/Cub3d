/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:19:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 18:04:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include <pthread.h>
# include <stdatomic.h>

# include "assets/assets.h"
# include "world/world.h"
# include "hooks/hooks.h"

typedef struct s_physics {
	t_world_buffer	*world_buffer;
	t_input			*input;
	t_assets		*assets;
	pthread_t		thread;
	atomic_int		running;
	char			reserved[4];
}	t_physics;

int		physics_init(t_physics *p);
void	physics_deinit(t_physics *p);
void	physics_update(t_physics *p, float dt);

void	debug_print_steps_per_sec(void);

#endif
