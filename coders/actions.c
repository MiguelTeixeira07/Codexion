/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/06 22:17:42 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	compile(t_coder *coder)
{
	pthread_mutex_lock(coder->table_mutex);
	printf("Waiting to be added to the queue...\n");
	coder->waiting = 1;
	pthread_cond_wait(coder->condition, coder->table_mutex);
	pthread_mutex_unlock(coder->table_mutex);
	pthread_mutex_lock(coder->self_mutex);
	printf("Waiting to compile...\n");
	pthread_cond_wait(coder->condition, coder->self_mutex);
	pthread_mutex_lock(coder->right_dongle);
	pthread_mutex_lock(coder->left_dongle);
	printf("\ncoder %d compiling...\n\n", coder->number);
	usleep(coder->prog_args->time_to_compile * 1000);
	pthread_mutex_unlock(coder->right_dongle);
	pthread_mutex_unlock(coder->left_dongle);
	pthread_mutex_unlock(coder->self_mutex);
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
