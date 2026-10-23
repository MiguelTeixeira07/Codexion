/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:30 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/23 18:25:31 by migteixe         ###   ########.fr       */
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
		if (check_end(coder->table))
			return (1);
		now = gettime();
		if (now - start >= duration_ms)
			break ;
		//usleep(500);
	}
	pthread_mutex_lock(coder->self_mutex);
	return (0);
}

static void	wait_in_list(t_coder *coder)
{
	//struct timespec	abstime;

	pthread_mutex_lock(coder->table->table_mutex);
	coder->waiting = 1;
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
	coder->waiting = 0;
	coder->in_queue = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
	pthread_mutex_lock(coder->self_mutex);
	pthread_cond_wait(coder->condition, coder->self_mutex);
	pthread_mutex_unlock(coder->self_mutex);
}

static int	take_dongles(t_coder *coder)
{
	int	lflag;
	int	rflag;

	lflag = 0;
	rflag = 0;
	while (1)
	{
		if (check_end(coder->table))
			return (1);
		if (coder->left_dongle->last_used + coder->table->args->dongle_cooldown < gettime() && !lflag)
		{
			lflag = 1;
			log_msg("has taken a dongle", coder->table, coder->number);
		}
		if (coder->right_dongle->last_used + coder->table->args->dongle_cooldown < gettime() && !rflag && coder->table->args->num_coders != 1)
		{
			rflag = 1;
			log_msg("has taken a dongle", coder->table, coder->number);
		}
		if (lflag && rflag)
			break ;
		//usleep(500);
	}
	return (0);
}

int	compile(t_coder *coder)
{
	wait_in_list(coder);
	pthread_mutex_lock(coder->self_mutex);
	coder->compiling = 1;
	pthread_mutex_unlock(coder->self_mutex);
	pthread_mutex_lock(coder->table->table_mutex);
	coder->table->coders_compiling++;
	pthread_mutex_unlock(coder->table->table_mutex);
	if (take_dongles(coder))
		return (1);
	log_msg("is compiling", coder->table, coder->number);
	pthread_mutex_lock(coder->self_mutex);
	coder->last_compile_start = gettime();
	coder->in_queue = 0;
	if (smart_sleep(coder->table->args->time_to_compile, coder))
		return (1);
	coder->compiling = 0;
	coder->compile_ammount++;
	pthread_mutex_lock(coder->right_dongle->dongle);
	coder->right_dongle->last_used = gettime();
	pthread_mutex_unlock(coder->right_dongle->dongle);
	pthread_mutex_lock(coder->left_dongle->dongle);
	coder->left_dongle->last_used = gettime();
	pthread_mutex_unlock(coder->left_dongle->dongle);
	pthread_mutex_unlock(coder->self_mutex);
	pthread_mutex_lock(coder->table->table_mutex);
	coder->table->coders_compiling--;
	pthread_mutex_unlock(coder->table->table_mutex);
	return (0);
}

int	debug_and_refactor(t_coder *coder)
{
	int	sleep_res;

	usleep(100);
	log_msg("is debugging", coder->table, coder->number);
	pthread_mutex_lock(coder->self_mutex);
	sleep_res = smart_sleep(coder->table->args->time_to_debug, coder);
	if (sleep_res)
		return sleep_res;
	pthread_mutex_unlock(coder->self_mutex);
	log_msg("is refactoring", coder->table, coder->number);
	pthread_mutex_lock(coder->self_mutex);
	sleep_res = smart_sleep(coder->table->args->time_to_refactor, coder);
	if (sleep_res)
		return sleep_res;
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}
