/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/16 22:18:40 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include <pthread.h>


int	check_end(t_table *table, t_coder *coder)
{
	__time_t	now;

	if (table->finished == table->args->num_coders || table->dead_coder) // data race
		return (1);
	if (!coder)
		return (0);
	pthread_mutex_lock(coder->self_mutex);
	if (coder->compile_ammount >= table->args->num_compiles && !coder->has_finished)
	{
		coder->has_finished = 1;
		table->finished++;
	}
	now = gettime() - table->sim_start;
	if (now - coder->last_compile_start >= table->args->time_to_burnout)
	{
		log_msg("burned out", table, coder->number);
		table->dead_coder = 1; // data race
		pthread_mutex_unlock(coder->self_mutex);
		return (1);
	}
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}

void	*monitor_routine(void *args)
{
	t_queue			*queue;
	t_table			*table;

	table = (t_table *)args;
	wait_for_start(table);
	queue = gar_col(ALLOC, sizeof(t_queue));
	table->sim_start = gettime();
	while (table->finished < table->args->num_coders)
	{
		pthread_mutex_lock(table->table_mutex);
		if (check_end(table, NULL))
		{
			log_msg("Simulation ended, Monitor stopping", table, 0);
			return (NULL);
		}
		update_queue(queue, table);
		allow_compiles(queue);
		pthread_mutex_unlock(table->table_mutex);
		usleep(10000);
	}
	return (NULL);
}

int	start_simulation(t_args *args)
{
	int			i;
	t_table		*table;
	pthread_t	monitor;

	table = init_table(args);
	if (!table)
		return -1;
	i = 0;
	while (++i <= args->num_coders)
	{
		if (table_push(table, i)) {
			return -1;
		}
	}
	return (create_threads(table, &monitor));
}
