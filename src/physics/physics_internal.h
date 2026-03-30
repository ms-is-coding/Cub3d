/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarnie <macarnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 20:49:25 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/03/30 21:29:33 by macarnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_INTERNAL_H
# define PHYSICS_INTERNAL_H

# include <stddef.h>

# include "assets/assets.h"
# include "world/world.h"
# include "hooks/hooks.h"

# include "physics.h"

typedef union u_hitbox {
	struct {
		t_vec2i	x;
		t_vec2i	y;
	};
	t_vec2i	e[2];
}	t_hitbox;

typedef void	(*t_entity_update_fn)(t_world *w,
									size_t i,
									t_input *k,
									float dt
									);

void	apply_collision(t_world *world, t_assets *assets, int axis);

void	player_update(t_world *world, t_assets *a, t_input *input);

float	door_offset_at(const t_world *w, int32_t tx, int32_t ty);
void	toggle_door(t_world *world);
void	door_update(t_world *world, size_t i, t_input *input, float dt);

void	entities_update(t_world *world, t_input *input, float dt);

void	physics_update(t_physics *p, float dt);

void	debug_print_steps_per_sec(void);

#endif
