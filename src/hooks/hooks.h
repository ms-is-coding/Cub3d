/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:37:21 by smamalig          #+#    #+#             */
/*   Updated: 2026/03/16 12:33:19 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdbool.h>
# include <stdint.h>

# include "engine/engine.h"

int	hooks_keys_init(t_engine *engine);
int	hooks_mouse_init(t_engine *engine);

#endif
