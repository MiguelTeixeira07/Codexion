/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:50:37 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"


/* static int	check_end(t_table *table)
{
	t_coder	*curr;
	int		i;

	curr = table->first;
	i = 0;
	while(++i <= table->num_coders)
	{
		if (curr->compile_ammount >= curr->prog_args->num_compiles)
			table->finished++;
		curr = curr->next;
	}
	return 0;
} */

void	*monitor_routine(void *args)
{
	t_queue	*queue;
	t_table	*table;
	t_coder	*curr_c;
	t_node	*curr_q;
	int		i;

	table = (t_table *)args;
	printf("Monitor just woke tf up!\n");
	pthread_mutex_lock(table->table_mutex);
	pthread_cond_wait(table->condition, table->table_mutex);
	pthread_mutex_unlock(table->table_mutex);
	queue = gar_col(ALLOC, sizeof(t_queue));
	while (table->finished < table->num_coders)
	{
		i = 0;
		curr_c = table->first;
		printf("does ts run?\n");
		pthread_mutex_lock(table->table_mutex);
		while (++i <= table->num_coders)
		{
			if (curr_c->waiting)
			{
				queue_push(queue, curr_c, curr_c->prog_args->scheduler);
				pthread_cond_signal(curr_c->condition);
				pthread_mutex_unlock(table->table_mutex);
				continue ;
			}
			curr_c = curr_c->next;
		}

		i = 0;
		while (curr_q)
		{
			if (curr_q->n_compiles < curr_q->coder->compile_ammount)
				queue_remove(queue, curr_q);

			pthread_mutex_lock(curr_q->coder->self_mutex);
			if (!(curr_q->coder->next->compiling || curr_q->coder->prev->compiling))
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

void	start_simulation(t_args *args)
{
	int			i;
	t_table		*table;
	pthread_t	monitor;

	table = init_table();
	if (!table)
		return ;
	i = -1;
	pthread_mutex_lock(table->table_mutex);
	//printf("%d\n", table->num_coders);
	pthread_mutex_unlock(table->table_mutex);
	while (++i < args->num_coders)
	{
		if (table_push(table, args, i)) {
			return ;
		}
	}
	//pthread_mutex_lock(table->table_mutex);
	create_threads(table, &monitor);
	printf("something\n");
	//pthread_mutex_unlock(table->table_mutex);
	return ;
}
