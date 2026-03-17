/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:10:38 by fadzejli          #+#    #+#             */
/*   Updated: 2026/03/16 12:41:00 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>

# include "cub3d.h"
# include "gfx/gfx.h"
# include <stdatomic.h>
# include <stdint.h>
# include <stdbool.h>
# include "threads/threads.h"

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;


// typedef struct s_game
// {
// 	t_data			*data;
// 	void			*mlx;
// 	void			*win;
// 	void			*img;
// 	uint32_t		*addr;
// 	t_threadpool	pool;
// 	t_gfx			gfx;
// 	t_options		opt;
// 	t_input			input;
// 	t_player		player;
// 	int				bpp;
// 	int				endian;
// 	int				size_len;
// 	int				texture_count;
// 	char			reserved[4];
// 	t_texture		textures[4];
// 	double			last_time;
// 	double			delta;
// }	t_game;

// void		game_destroy(t_game *game, int exit_code)
// 			__attribute__((noreturn));

// int			init_game(t_game *game, t_data *data);
// int			load_texture(t_game *game, t_texture *tex, char *path);
// void		raycast(t_game *game);
// void		calculate_distances(t_ray *ray);
// void		print_ray(t_ray *ray, t_game *game, uint32_t x);
// t_texture	*get_texture(t_ray *ray, t_game *game);
// uint32_t	check_pos(float pos, t_texture *tex);
// uint32_t	get_color(t_texture *tex, uint32_t x, uint32_t y);

// float		find_intersection(t_ray *ray, t_player player);
// int			quit_game(t_game *game);
// int			key_press(int key_code, t_game *game);

// int			hooks_init(t_game *game);

// #endif
