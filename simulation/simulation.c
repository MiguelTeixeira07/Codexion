/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/13 21:35:50 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include <pthread.h>


int	check_end(t_table *table)
{
	t_coder			*curr;
	int				i;
	int				finished;
	int				return_val;

	pthread_mutex_lock(table->table_mutex);
	finished = 0;
	curr = table->first;
	i = 0;
	while(++i <= table->args->num_coders)
	{
		if (table->dead_coders)
		{
			pthread_mutex_unlock(table->table_mutex);
			return (2);
		}
		if (curr->compile_ammount >= curr->table->args->num_compiles)
			finished++;
		curr = curr->next;
	}
	table->finished = finished;
	return_val = (table->finished == table->args->num_coders);
	pthread_mutex_unlock(table->table_mutex);
	return (return_val);
}

void	*monitor_routine(void *args)
{
	t_queue			*queue;
	t_table			*table;
	t_coder			*curr_c;
	t_node			*curr_q;
	t_node			*next;
	int				i;

	table = (t_table *)args;
	printf("Monitor was just created\n");
	pthread_mutex_lock(table->table_mutex);
	pthread_cond_wait(table->condition, table->table_mutex);
	pthread_mutex_unlock(table->table_mutex);
	printf("Monitor just woke tf up!\n");
	queue = gar_col(ALLOC, sizeof(t_queue));
	usleep(1000000);
	while (table->finished < table->args->num_coders)
	{
		pthread_mutex_lock(table->table_mutex);
		if (table->result)
		{
			printf("This is not supposed to happen %d\n", table->result);
			return (NULL);
		}
		i = 0;
		curr_c = table->first;
		while (++i <= table->args->num_coders)
		{
			if (curr_c->waiting)
			{
				queue_push(queue, curr_c, curr_c->table->args->scheduler);
				curr_c->waiting = 0;
				pthread_mutex_unlock(table->table_mutex);
				pthread_cond_signal(curr_c->condition);
				usleep(1000);
				pthread_mutex_lock(table->table_mutex);
			}
			curr_c = curr_c->next;
		}
		print_queue(queue);
		curr_q = queue->top;
		while (curr_q)
		{
			if (!curr_q->coder->in_queue)
			{
				next = curr_q->next;
				queue_remove(queue, curr_q);
				curr_q = next;
				if (!curr_q)
					break ;
			}
			pthread_mutex_lock(curr_q->coder->self_mutex);
			if (!curr_q->coder->next->compiling && !curr_q->coder->prev->compiling)
			{
				curr_q->n_compiles = curr_q->coder->compile_ammount;
				pthread_mutex_unlock(curr_q->coder->self_mutex);
				pthread_cond_signal(curr_q->coder->condition);
				usleep(1000);
				curr_q = curr_q->next;
				continue ;
			}
			pthread_mutex_unlock(curr_q->coder->self_mutex);
			curr_q = curr_q->next;
		}
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
	pthread_mutex_lock(table->table_mutex);
	//printf("%d\n", table->num_coders);
	pthread_mutex_unlock(table->table_mutex);
	while (++i <= args->num_coders)
	{
		if (table_push(table, i)) {
			return -1;
		}
	}
	//pthread_mutex_lock(table->table_mutex);
	return (create_threads(table, &monitor));
	//pthread_mutex_unlock(table->table_mutex);
}
