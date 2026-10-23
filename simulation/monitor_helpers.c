/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 17:07:27 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/23 17:02:12 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"

void	update_queue(t_queue *queue, t_table *table)
{
	t_coder	*curr;
	int		i;
	int		waiting;

	i = 0;
	curr = table->first;
	while (++i <= table->args->num_coders)
	{
		pthread_mutex_lock(curr->self_mutex);
		waiting = curr->waiting;
		pthread_mutex_unlock(curr->self_mutex);
		if (waiting)
		{
			queue_push(queue, curr, curr->table->args->scheduler);
			pthread_mutex_lock(curr->self_mutex);
			pthread_cond_signal(curr->condition);
			pthread_mutex_unlock(curr->self_mutex);
			pthread_mutex_unlock(table->table_mutex);
			usleep(50);
			pthread_mutex_lock(table->table_mutex);
		}
		curr = curr->next;
	}
}

void	allow_compiles(t_queue *queue)
{
	t_node	*curr_q;
	t_node	*prev;
	int		cond1;
	int		cond2;

	curr_q = queue->top;
	while (curr_q)
	{
		prev = curr_q;
		pthread_mutex_lock(curr_q->coder->self_mutex);
		if (!curr_q->coder->in_queue)
		{
			curr_q = queue_remove(queue, curr_q);
			if (!curr_q)
			{
				pthread_mutex_unlock(prev->coder->self_mutex);
				break ;
			}
		}
		pthread_mutex_unlock(prev->coder->self_mutex);
		pthread_mutex_lock(curr_q->coder->prev->self_mutex);
		cond1 =  !curr_q->coder->prev->compiling;
		pthread_mutex_unlock(curr_q->coder->prev->self_mutex);
		pthread_mutex_lock(curr_q->coder->next->self_mutex);
		cond2 = !curr_q->coder->next->compiling;
		pthread_mutex_unlock(curr_q->coder->next->self_mutex);
		if (cond1 && cond2)
		{
			pthread_mutex_lock(curr_q->coder->self_mutex);
			curr_q->n_compiles = curr_q->coder->compile_ammount;
			pthread_cond_signal(curr_q->coder->condition);
			pthread_mutex_unlock(curr_q->coder->self_mutex);
			usleep(50);
		}
		curr_q = curr_q->next;
	}
}

void	update_end(t_table *table)
{
	__time_t	now;
	t_coder		*coder;
	int			i;

	coder = table->first;
	i = 0;
	pthread_mutex_lock(table->table_mutex);
	while (++i <= table->args->num_coders)
	{
		pthread_mutex_lock(coder->self_mutex);
		if (coder->compile_ammount >= table->args->num_compiles && !coder->has_finished)
		{
			coder->has_finished = 1;
			table->finished++;
		}
		now = gettime() - table->sim_start;
		if (now - coder->last_compile_start >= table->args->time_to_burnout)
		{
			pthread_mutex_unlock(coder->self_mutex);
			pthread_mutex_unlock(table->table_mutex);
			log_msg("burned out", table, coder->number);
			pthread_mutex_lock(table->table_mutex);
			table->dead_coder = 1;
			pthread_mutex_unlock(table->table_mutex);
			return ;
		}
		pthread_mutex_unlock(coder->self_mutex);
		coder = coder->next;
	}
	pthread_mutex_unlock(table->table_mutex);
}

void	wait_for_start(t_table *table)
{
	pthread_mutex_lock(table->table_mutex);
	pthread_cond_wait(table->condition, table->table_mutex);
	pthread_mutex_unlock(table->table_mutex);
	usleep(1000000);
}
