/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:35:08 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 19:55:18 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "../../lib/libft/libft.h"
# include "assets/assets.h"
# include "gfx/gfx.h"
# include "hooks/hooks.h"
# include "world/world.h"
# include "physics/physics.h"
# include "renderer/renderer.h"

typedef int	(*t_hook_fn)(void);

typedef struct s_engine {
	t_options		opt;
	t_input			input;
	t_assets		assets;
	t_gfx			gfx;
	t_world_buffer	world_buffer;
	t_physics		physics;
	t_renderer		renderer;
}	t_engine;

int		engine_init(t_engine *e, int argc, char **argv);
void	engine_deinit(t_engine *e);

#endif
