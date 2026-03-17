/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/16 22:39:40 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include "gfx/gfx.h"
#include "assets/assets.h"
#include "engine/engine.h"
#include "renderer/renderer.h"

// __attribute__((__noreturn__))
// void	game_destroy(t_game *g, int exit_code)
// {
// 	gfx_deinit(&g->gfx);
// 	exit(exit_code);
// }

#define MOVE_STEP 0.01f
#define ROT_STEP 0.01f

__attribute__((unused))
static int	loop2(t_engine *e)
{
	renderer_render(&e->renderer);
	gfx_present(&e->gfx, renderer_get_ready_frame(&e->renderer));
	return (0);
}

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (!engine_init(&engine, argc, argv))
		return (1);
	// hooks_init(&game);
	gfx_loop(&engine.gfx, (int (*)(void))(intptr_t)loop2, &engine);
	return (0);
}
