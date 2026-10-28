/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/27 18:31:53 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "../garbage_collector/garbage_collector.h"

int	check_end(t_table *table)
{
	pthread_mutex_lock(table->table_mutex);
	if (table->finished >= table->args->num_coders || table->dead_coder)
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
	queue = gar_col(ALLOC, sizeof(t_queue));
	prepare_monitor(table, queue);
	while (!can_terminate)
	{
		update_end(table);
		end = check_end(table);
		pthread_mutex_lock(table->table_mutex);
		can_terminate = table->terminated_coders == table->args->num_coders;
		if (table->coders_compiling < 1 || end)
		{
			allow_compiles(queue);
			update_queue(queue, table);
		}
		pthread_mutex_unlock(table->table_mutex);
		usleep(1000);
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
		return (-1);
	i = 0;
	while (++i <= args->num_coders)
	{
		if (table_push(table, i))
			return (-1);
	}
	return (create_threads(table, &monitor));
}
