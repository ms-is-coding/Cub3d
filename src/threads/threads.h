/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:37:15 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 12:35:45 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <pthread.h>
# include <stdint.h>

# define MAX_TASKS 256

typedef void	(*t_task_fn)(void *);

typedef struct s_task {
	t_task_fn	fn;
	void		*arg;
}	t_task;

typedef struct s_threadpool {
	pthread_t		*threads;
	t_task			task_queue[MAX_TASKS];
	int				task_count;
	int				task_index;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	pthread_cond_t	done_cond;
	int				active_workers;
	int				stop;
	int				thread_count;
	char			reserved[4];
}	t_threadpool;

int		threadpool_init(t_threadpool *pool, int worker_count);
void	threadpool_add(t_threadpool *pool, t_task_fn fn, void *arg);
void	threadpool_run(t_threadpool *pool);
void	threadpool_deinit(t_threadpool *pool);

#endif
