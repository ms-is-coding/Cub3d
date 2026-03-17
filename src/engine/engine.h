/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:35:08 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 22:38:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "assets/assets.h"
# include "gfx/gfx.h"
# include "world/world.h"
# include "physics/physics.h"
# include "renderer/renderer.h"

typedef int	(*t_hook_fn)(void);

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

typedef struct s_input {
	t_keys	keys;
}	t_input;

typedef struct s_engine {
	t_options		opt;
	t_assets		assets;
	t_gfx			gfx;
	t_world_buffer	world_buffer;
	t_physics		physics;
	t_renderer		renderer;
	t_input			input;

	void			*mlx;
}	t_engine;

int		engine_init(t_engine *e, int argc, char **argv);
void	engine_deinit(t_engine *e);

#endif
