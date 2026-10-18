/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/18 00:52:01 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include <pthread.h>


int	check_end(t_table *table, t_coder *coder)
{
	__time_t	now;

	pthread_mutex_lock(table->table_mutex);
	if (table->finished == table->args->num_coders || table->dead_coder)
	{
		pthread_mutex_unlock(table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(table->table_mutex);
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
		pthread_mutex_unlock(coder->self_mutex);
		pthread_mutex_lock(table->table_mutex);
		table->dead_coder = 1;
		pthread_mutex_unlock(table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(coder->self_mutex);
	return (0);
}

void	*monitor_routine(void *args)
{
	t_queue			*queue;
	t_table			*table;
	int				can_terminate;

	table = (t_table *)args;
	can_terminate = 0;
	wait_for_start(table);
	queue = gar_col(ALLOC, sizeof(t_queue));
	pthread_mutex_lock(table->table_mutex);
	table->sim_start = gettime();
	pthread_mutex_unlock(table->table_mutex);
	while (!check_end(table, NULL) || !can_terminate)
	{
		pthread_mutex_lock(table->table_mutex);
		can_terminate = table->terminated_coders == table->args->num_coders;
		update_queue(queue, table);
		allow_compiles(queue);
		pthread_mutex_unlock(table->table_mutex);
		usleep(100);
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
