/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/20 01:59:27 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "../parsing/parser.h"

void	compile(t_coder_args *args)
{
	usleep(args->time_to_compile * 1000);
	usleep(args->dongle_cooldown * 1000);
}

void	debug(t_coder_args *args)
{
	usleep(args->time_to_debug);
}

void	refactor(t_coder_args *args)
{
	usleep(args->time_to_refactor * 1000);
}
