/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/10 19:19:23 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	compile(t_coder *coder)
{
	struct timeval	time;

	pthread_mutex_lock(coder->table->table_mutex);
	//printf("%d Waiting to be added to the queue...\n", coder->number);
	coder->waiting = 1;
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
	pthread_mutex_unlock(coder->table->table_mutex);
	pthread_mutex_lock(coder->self_mutex);
	//printf("%d Waiting to compile...\n", coder->number);
	pthread_cond_wait(coder->condition, coder->self_mutex);
	pthread_mutex_lock(coder->right_dongle);
	pthread_mutex_lock(coder->left_dongle);
	gettimeofday(&time, NULL);
	coder->last_compile_start = (float)(
		time.tv_sec * 1000000 + time.tv_usec
	);
	coder->compile_ammount++;
	printf("coder %d compiling...\n", coder->number);
	usleep(coder->table->args->time_to_compile * 1000);
	pthread_mutex_unlock(coder->right_dongle);
	pthread_mutex_unlock(coder->left_dongle);
	pthread_mutex_unlock(coder->self_mutex);
}

void	debug_and_refactor(t_coder *coder)
{
	printf("coder %d debugging...\n", coder->number);
	usleep(coder->table->args->time_to_debug * 1000);
	printf("coder %d refactoring...\n", coder->number);
	usleep(coder->table->args->time_to_refactor * 1000);
}
