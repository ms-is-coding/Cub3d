/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fadwa <fadwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:19:40 by macarnie          #+#    #+#             */
/*   Updated: 2026/03/30 19:39:33 by fadwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "world.h"

void	world_buffer_deinit(t_world_buffer *wb)
{
	if (!wb)
		return ;
	ft_memset(wb, 0, sizeof(t_world_buffer));
}
