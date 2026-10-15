/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/14 17:55:07 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


static int	smart_sleep(long duration_ms, t_coder *coder)
{
	__time_t	start;
	__time_t	now;
	int			finished;

	start = gettime();
	pthread_mutex_unlock(coder->self_mutex);
	while (1)
	{
		//log_msg("waiting in smart sleep...", coder->table->log_mutex, coder->number);
		finished = 0;//check_end(coder->table);
		if (finished)
		{
			pthread_mutex_lock(coder->self_mutex);
			return (finished);
		}
		now = gettime();
		//printf("start: %ld\t|\tnow: %ld\t|\tduration: %ld\t|\tdelta: %ld\n", start, now, duration_ms, (now - start));
		if (now - start >= duration_ms)
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(coder->self_mutex);
	log_msg("Got here", coder->table->log_mutex, coder->number);
	return (0);
}

int	compile(t_coder *coder)
{
	pthread_mutex_lock(coder->table->table_mutex);
	coder->waiting = 1;
	log_msg("Waiting to be added to the queue...", coder->table->log_mutex, coder->number);
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
	coder->waiting = 0;
	log_msg("I was added to the queue", coder->table->log_mutex, coder->number);
	coder->in_queue = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
	log_msg("Locking self mutex", coder->table->log_mutex, coder->number);
	pthread_mutex_lock(coder->self_mutex);
	log_msg("Waiting to compile...", coder->table->log_mutex, coder->number);
	pthread_cond_wait(coder->condition, coder->self_mutex);
	pthread_mutex_lock(coder->right_dongle);
	pthread_mutex_lock(coder->left_dongle);
	coder->last_compile_start = gettime();
	coder->compiling = 1;
	coder->in_queue = 0;
	coder->compile_ammount++;
	log_msg("Compiling...", coder->table->log_mutex, coder->number);
	if (smart_sleep(coder->table->args->time_to_compile, coder))
		return 1;
	log_msg("Finished compiling", coder->table->log_mutex, coder->number);
	coder->compiling = 0;
	pthread_mutex_unlock(coder->left_dongle);
	pthread_mutex_unlock(coder->right_dongle);
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}

int	debug_and_refactor(t_coder *coder)
{
	int	sleep_res;

	log_msg("Debugging...", coder->table->log_mutex, coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_debug, coder);
	if (sleep_res)
		return sleep_res;
	log_msg("Refactoring...", coder->table->log_mutex, coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_refactor, coder);
	if (sleep_res)
		return sleep_res;
	return (0);
}
