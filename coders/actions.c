/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/16 22:15:27 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include <pthread.h>

static int	smart_sleep(long duration_ms, t_coder *coder)
{
	__time_t	start;
	__time_t	now;

	start = gettime();
	pthread_mutex_unlock(coder->self_mutex);
	while (1)
	{
		if (check_end(coder->table, coder))
			return (1);
		now = gettime();
		if (now - start >= duration_ms)
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(coder->self_mutex);
	return (0);
}

static void	wait_in_list(t_coder *coder)
{
	pthread_mutex_lock(coder->table->table_mutex);
	coder->waiting = 1;
	//log_msg("Waiting to be added to the queue...", coder->table->log_mutex, coder->number);
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
	coder->waiting = 0;
	//log_msg("I was added to the queue", coder->table->log_mutex, coder->number);
	coder->in_queue = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
	//log_msg("Locking self mutex", coder->table->log_mutex, coder->number);
	pthread_mutex_lock(coder->self_mutex);
	//log_msg("Waiting to compile...", coder->table->log_mutex, coder->number);
	pthread_cond_wait(coder->condition, coder->self_mutex);
	pthread_mutex_unlock(coder->self_mutex);
}

static int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->dongle);
	while (dongle->last_used + coder->table->args->dongle_cooldown > gettime())
	{
		if (check_end(coder->table, coder))
		{
			pthread_mutex_unlock(dongle->dongle);
			return (1);
		}
		usleep(1000);
	}
	if (check_end(coder->table, coder))
	{
		pthread_mutex_unlock(dongle->dongle);
		return (1);
	}
	log_msg("has taken a dongle", coder->table, coder->number);
	return (0);
}

int	compile(t_coder *coder)
{
	wait_in_list(coder);
	if (take_dongle(coder, coder->left_dongle))
		return (1);
	if (take_dongle(coder, coder->right_dongle))
	{
		pthread_mutex_unlock(coder->left_dongle->dongle);
		return (1);
	}
	pthread_mutex_lock(coder->self_mutex);
	coder->last_compile_start = gettime();
	coder->compiling = 1;
	coder->in_queue = 0;
	coder->compile_ammount++;
	log_msg("is compiling", coder->table, coder->number);
	if (smart_sleep(coder->table->args->time_to_compile, coder))
		return (1);
	coder->compiling = 0;
	coder->right_dongle->last_used = gettime();
	pthread_mutex_unlock(coder->right_dongle->dongle);
	coder->left_dongle->last_used = gettime();
	pthread_mutex_unlock(coder->left_dongle->dongle);
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}

int	debug_and_refactor(t_coder *coder)
{
	int	sleep_res;

	pthread_mutex_lock(coder->self_mutex);
	log_msg("Debugging...", coder->table, coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_debug, coder);
	if (sleep_res)
		return sleep_res;
	log_msg("Refactoring...", coder->table, coder->number);
	sleep_res = smart_sleep(coder->table->args->time_to_refactor, coder);
	if (sleep_res)
		return sleep_res;
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}
