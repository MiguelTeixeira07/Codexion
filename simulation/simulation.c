/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/14 17:56:20 by migteixe         ###   ########.fr       */
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
		pthread_mutex_lock(curr->self_mutex);
		if (table->dead_coder)
		{
			pthread_mutex_unlock(curr->self_mutex);
			pthread_mutex_unlock(table->table_mutex);
			return (table->dead_coder);
		}
		if (curr->compile_ammount >= curr->table->args->num_compiles)
			finished++;
		curr = curr->next;
		pthread_mutex_unlock(curr->self_mutex);
	}
	table->finished = finished;
	return_val = (table->finished == table->args->num_coders);
	pthread_mutex_unlock(table->table_mutex);
	return (-return_val);
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
		log_msg("Monitor running.", table->log_mutex, 0);
		pthread_mutex_lock(table->table_mutex);
		if (table->result)
		{
			log_msg("This is not supposed to happen.", table->log_mutex, 0);
			return (NULL);
		}
		i = 0;
		curr_c = table->first;
		log_msg("Deadlock?", table->log_mutex, 0);
		while (++i <= table->args->num_coders)
		{
			if (curr_c->waiting)
			{
				log_msg("Deadlock?1", table->log_mutex, 0);
				queue_push(queue, curr_c, curr_c->table->args->scheduler);
				pthread_mutex_unlock(table->table_mutex);
				pthread_cond_signal(curr_c->condition);
				//printf("Monitor: Added coder %d to the queue\n", curr_c->number);
				usleep(1000);
				pthread_mutex_lock(table->table_mutex);
				print_queue(queue);
			}
			curr_c = curr_c->next;
		}
		curr_q = queue->top;
		log_msg("Deadlock?", table->log_mutex, 0);
		while (curr_q)
		{
			if (!curr_q->coder->in_queue)
			{
				next = curr_q->next;
				queue_remove(queue, curr_q);
				print_queue(queue);
				curr_q = next;
				if (!curr_q)
					break ;
			}
			log_msg("Deadlock?2c", table->log_mutex, 0);
			pthread_mutex_lock(curr_q->coder->self_mutex); // Deadlock
			log_msg("Deadlock?2", table->log_mutex, 0);
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
			printf("%d\n", (curr_q ? curr_q->coder->number : -1));
			log_msg("Deadlock?2a", table->log_mutex, 0);
		}
		log_msg("Deadlock?2b", table->log_mutex, 0);
		pthread_mutex_unlock(table->table_mutex);
		log_msg("Deadlock?2c", table->log_mutex, 0);
		log_msg("Deadlock?3", table->log_mutex, 0);
		usleep(10000);
	}
	log_msg("Monitor stopped running", table->log_mutex, 0);
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
	pthread_mutex_unlock(table->table_mutex);
	while (++i <= args->num_coders)
	{
		if (table_push(table, i)) {
			return -1;
		}
	}
	return (create_threads(table, &monitor));
}
