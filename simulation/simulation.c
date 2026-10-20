/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/21 00:05:36 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include <pthread.h>


int	check_end(t_table *table)
{
	pthread_mutex_lock(table->table_mutex);
	if (table->finished == table->args->num_coders || table->dead_coder)
	{
		pthread_mutex_unlock(table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(table->table_mutex);
	return (0);
}

void	*monitor_routine(void *args)
{
	t_queue			*queue;
	t_table			*table;
	int				can_terminate;
	int				end;

	table = (t_table *)args;
	can_terminate = 0;
	wait_for_start(table);
	queue = gar_col(ALLOC, sizeof(t_queue));
	pthread_mutex_lock(table->table_mutex);
	update_queue(queue, table);
	table->sim_start = gettime();
	pthread_mutex_unlock(table->table_mutex);
	while (!check_end(table) || !can_terminate)
	{
		update_end(table);
		end = check_end(table);
		pthread_mutex_lock(table->table_mutex);
		can_terminate = table->terminated_coders == table->args->num_coders;
		if (table->coders_compiling == 0 || end)
		{
			allow_compiles(queue);
			update_queue(queue, table);
		}
		pthread_mutex_unlock(table->table_mutex);
		usleep(25);
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
