/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/10 19:24:04 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"


static int	check_end(t_table *table)
{
	t_coder			*curr;
	int				i;
	int				finished;
	struct timeval	current_time;

	finished = 0;
	curr = table->first;
	i = 0;
	while(++i <= table->num_coders)
	{
		gettimeofday(&current_time, NULL);
		if (
			(int)(current_time.tv_sec * 1000000 + current_time.tv_usec) -
			curr->last_compile_start + table->args->time_to_compile >
			table->args->time_to_burnout
		) {
			printf("%f\n", ((int)(current_time.tv_sec * 1000000 + current_time.tv_usec) -
			curr->last_compile_start + table->args->time_to_compile));
			return (2);
		}
		if (curr->compile_ammount >= curr->table->args->num_compiles)
			finished++;
		curr = curr->next;
	}
	table->finished = finished;
	return (table->finished == table->num_coders);
}

void	*monitor_routine(void *args)
{
	t_queue	*queue;
	t_table	*table;
	t_coder	*curr_c;
	t_node	*curr_q;
	int		i;

	table = (t_table *)args;
	printf("Monitor was just created\n");
	pthread_mutex_lock(table->table_mutex);
	pthread_cond_wait(table->condition, table->table_mutex);
	pthread_mutex_unlock(table->table_mutex);
	printf("Monitor just woke tf up!\n");
	queue = gar_col(ALLOC, sizeof(t_queue));
	while (table->finished < table->num_coders)
	{
		table->result = check_end(table);
		if (table->result)
		{
			printf("This is not supposed to happen %d\n", table->result);
			return (NULL);
		}
		i = 0;
		curr_c = table->first;
		pthread_mutex_lock(table->table_mutex);
		//printf("Adding coders to the queue...\n");
		while (++i <= table->num_coders)
		{
			if (curr_c->waiting)
			{
				queue_push(queue, curr_c, curr_c->table->args->scheduler);
				pthread_cond_signal(curr_c->condition);
				pthread_mutex_unlock(table->table_mutex);
			}
			curr_c = curr_c->next;
		}

		i = 0;
		//printf("Getting coders to compile\n");
		while (curr_q)
		{
			if (curr_q->n_compiles < curr_q->coder->compile_ammount)
			{
				curr_q = curr_q->next;
				queue_remove(queue, curr_q->previous);
			}

			pthread_mutex_lock(curr_q->coder->self_mutex);
			if (!curr_q->coder->next->compiling && !curr_q->coder->prev->compiling)
			{
				curr_q->n_compiles = curr_q->coder->compile_ammount;
				pthread_cond_signal(curr_q->coder->condition);
				pthread_mutex_unlock(curr_q->coder->self_mutex);
			}
			curr_q = curr_q->next;
		}
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
	i = -1;
	pthread_mutex_lock(table->table_mutex);
	//printf("%d\n", table->num_coders);
	pthread_mutex_unlock(table->table_mutex);
	while (++i < args->num_coders)
	{
		if (table_push(table, i)) {
			return -1;
		}
	}
	//pthread_mutex_lock(table->table_mutex);
	return (create_threads(table, &monitor));
	//pthread_mutex_unlock(table->table_mutex);
}
