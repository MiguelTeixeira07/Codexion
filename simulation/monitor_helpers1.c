/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_helpers1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 17:07:27 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/27 18:44:28 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "../utils/utils.h"

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
			usleep(10);
			pthread_mutex_lock(table->table_mutex);
		}
		curr = curr->next;
	}
}

static void	set_conditions(t_node *curr, int *cond1, int *cond2)
{
	pthread_mutex_lock(curr->coder->prev->self_mutex);
	*cond1 = !curr->coder->prev->compiling;
	pthread_mutex_unlock(curr->coder->prev->self_mutex);
	pthread_mutex_lock(curr->coder->next->self_mutex);
	*cond2 = !curr->coder->next->compiling;
	pthread_mutex_unlock(curr->coder->next->self_mutex);
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
		set_conditions(curr_q, &cond1, &cond2);
		if (cond1 && cond2)
			order_compile(curr_q);
		curr_q = curr_q->next;
	}
}

void	update_end(t_table *table)
{
	t_coder		*coder;
	int			i;

	coder = table->first;
	i = 0;
	pthread_mutex_lock(table->table_mutex);
	while (++i <= table->args->num_coders)
	{
		pthread_mutex_lock(coder->self_mutex);
		if (coder->compile_ammount >= table->args->num_compiles
			&& !coder->has_finished)
		{
			coder->has_finished = 1;
			table->finished++;
		}
		if (gettime() - table->sim_start - coder->last_compile_start
			>= table->args->time_to_burnout)
		{
			burn_out(coder);
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
