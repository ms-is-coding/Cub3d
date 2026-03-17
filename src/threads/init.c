/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 19:44:44 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 12:37:19 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

#include "libft.h"
#include "common.h"

#include "threads.h"


static void	*worker_loop(void *arg)
{
	t_threadpool	*pool;
	t_task			task;

	pool = (t_threadpool *)arg;
	while (true)
	{
		pthread_mutex_lock(&pool->lock);
		while (pool->task_index >= pool->task_count && !pool->stop)
			pthread_cond_wait(&pool->cond, &pool->lock);
		if (pool->stop)
		{
			pthread_mutex_unlock(&pool->lock);
			break ;
		}
		task = pool->task_queue[pool->task_index++];
		pool->active_workers++;
		pthread_mutex_unlock(&pool->lock);
		task.fn(task.arg);
		pthread_mutex_lock(&pool->lock);
		if (--pool->active_workers == 0 && pool->task_index >= pool->task_count)
			pthread_cond_signal(&pool->done_cond);
		pthread_mutex_unlock(&pool->lock);
	}
	return (NULL);
}

static int	get_available_cpus(void)
{
	const long	cpu_count = sysconf(_SC_NPROCESSORS_ONLN);

	if (cpu_count == -1 || cpu_count > MAX_THREADS)
	{
		dprintf(2, "Warning: multithreading not available\n");
		return (0);
	}
	return ((int)cpu_count);
}

int	threadpool_init(t_threadpool *pool, int worker_count)
{
	int	i;

	if (worker_count == -1)
		worker_count = get_available_cpus();
	if (worker_count == 0)
		return (1);
	printf("CPUs: %i\n", worker_count);
	ft_memset(pool, 0, sizeof(t_threadpool));
	pool->threads = ft_calloc((size_t)worker_count, sizeof(pthread_t));
	if (!pool->threads)
		return (1);
	pthread_mutex_init(&pool->lock, NULL);
	pthread_cond_init(&pool->cond, NULL);
	pthread_cond_init(&pool->done_cond, NULL);
	i = -1;
	while (++i < worker_count)
	{
		if (pthread_create(&pool->threads[i], NULL, worker_loop, pool) != 0)
		{
			threadpool_deinit(pool);
			return (1);
		}
		pool->thread_count++;
	}
	return (0);
}
