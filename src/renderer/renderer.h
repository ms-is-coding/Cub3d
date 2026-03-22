/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:16:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/22 10:52:35 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "assets/assets.h"
# include "common.h"
# include "gfx/gfx.h"
# include "options/options.h"
# include "threads/threads.h"
# include "world/world.h"
# include <stdatomic.h>
# include <stdint.h>

typedef struct s_renderer
{
	const t_options	*options;
	const t_gfx		*gfx;
	const t_assets	*assets;
	t_world_buffer	*world_buffer;
	t_image			framebuffers[FRAMEBUFFER_COUNT];
	t_threadpool	pool;

	atomic_int		ready_index;
	int				render_index;
	int				fps_limit;
	char			reserved[4];
	long			frame_time_us;
	long			next_frame_time;
}	t_renderer;

int				renderer_init(t_renderer *r, const t_options *opt);
void			renderer_deinit(t_renderer *r);

void			renderer_render(t_renderer *r);

const t_image	*renderer_get_ready_frame(const t_renderer *r);
t_image			*renderer_get_render_frame(t_renderer *r);
void			renderer_publish_frame(t_renderer *r);

#endif
