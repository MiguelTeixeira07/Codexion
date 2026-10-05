/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/04 16:11:48 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	compile(t_coder *coder)
{
	printf("\ncoder %d compiling...\n\n", coder->number);
	usleep(coder->prog_args->time_to_compile * 1000);
	usleep(coder->prog_args->dongle_cooldown * 1000);
}

void	debug(t_coder *coder)
{
	printf("coder %d debugging...\n", coder->number);
	usleep(coder->prog_args->time_to_debug * 1000);
}

void	refactor(t_coder *coder)
{
	printf("coder %d refactoring...\n", coder->number);
	usleep(coder->prog_args->time_to_refactor * 1000);
}
