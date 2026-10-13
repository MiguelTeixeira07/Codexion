/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/12 23:44:37 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


static int	smart_sleep(long duration_ms, t_table *table)
{
	__time_t	start;
	__time_t	now;
	int			finished;

	start = gettime();
	while (1)
	{
		finished = check_end(table);
		if (finished)
			return (finished);
		now = gettime();
		//printf("start: %lf\t|\tnow: %lf\n", start, now);
		if (now - start >= duration_ms)
			break ;
		usleep(500);
	}
	return (0);
}

int	compile(t_coder *coder)
{
	int				sleep_res;

	pthread_mutex_lock(coder->table->table_mutex);
	log_msg("Waiting to be added to the queue...", coder->log_mutex, coder->number);
	coder->waiting = 1;
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
	log_msg("I was added to the queue", coder->log_mutex, coder->number);
	coder->in_queue = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
	log_msg("Locking self mutex", coder->log_mutex, coder->number);
	pthread_mutex_lock(coder->self_mutex);
	log_msg("Waiting to compile...", coder->log_mutex, coder->number);
	pthread_cond_wait(coder->condition, coder->self_mutex);
	pthread_mutex_lock(coder->right_dongle);
	pthread_mutex_lock(coder->left_dongle);
	coder->last_compile_start = gettime();
	coder->in_queue = 0;
	coder->compiling = 1;
	coder->compile_ammount++;
	log_msg("Compiling...", coder->log_mutex, coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_compile, coder->table);
	if (sleep_res)
		return sleep_res;
	log_msg("Finished compiling", coder->log_mutex, coder->number);
	coder->compiling = 0;
	pthread_mutex_unlock(coder->right_dongle);
	pthread_mutex_unlock(coder->left_dongle);
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}

int	debug_and_refactor(t_coder *coder)
{
	int	sleep_res;

	printf("coder %d debugging...\n", coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_debug, coder->table);
	if (sleep_res)
		return sleep_res;
	printf("coder %d refactoring...\n", coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_refactor, coder->table);
	if (sleep_res)
		return sleep_res;
	return (0);
}
