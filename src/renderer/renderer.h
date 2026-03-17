/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:16:51 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 12:38:40 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "common.h"
# include "gfx/gfx.h"
# include "options/options.h"
# include "threads/threads.h"
# include "world/world.h"
# include <stdatomic.h>
# include <stdint.h>

typedef struct s_renderer
{
	const t_gfx		*gfx;
	t_world_buffer	*world_buffer;
	t_image			framebuffers[FRAMEBUFFER_COUNT];
	t_threadpool	pool;

	atomic_int		ready_index;
	int				render_index;
	// bool MT;
	int				fps_limit;
	char			reserved[4];
	long			frame_time_us;
	long			next_frame_time;
}	t_renderer;

typedef struct s_render_task {
	t_renderer		*renderer;
	const t_world	*world;
	t_image			*frame;
	uint32_t		x_start;
	uint32_t		x_end;
}	t_render_task;

int				renderer_init(t_renderer *r, const t_options *opt);
void			renderer_deinit(t_renderer *r);

void			renderer_render(t_renderer *r);

const t_image	*renderer_get_ready_frame(const t_renderer *r);
t_image			*renderer_get_render_frame(t_renderer *r);
void			renderer_publish_frame(t_renderer *r);

#endif
