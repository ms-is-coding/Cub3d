/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:45:47 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/17 11:08:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets/assets.h"
#include "gfx/gfx.h"

#include "engine.h"

void	engine_deinit(t_engine *e)
{
	(void)e;
	assets_destroy(&e->assets);
}
