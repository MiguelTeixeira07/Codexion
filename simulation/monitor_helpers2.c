/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 18:10:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/27 18:33:59 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "../utils/utils.h"

void	order_compile(t_node *curr)
{
	pthread_mutex_lock(curr->coder->self_mutex);
	curr->n_compiles = curr->coder->compile_ammount;
	pthread_cond_signal(curr->coder->condition);
	pthread_mutex_unlock(curr->coder->self_mutex);
	usleep(10);
}

void	prepare_monitor(t_table *table, t_queue *queue)
{
	wait_for_start(table);
	pthread_mutex_lock(table->table_mutex);
	update_queue(queue, table);
	table->sim_start = gettime();
	pthread_mutex_unlock(table->table_mutex);
}

void	burn_out(t_coder *coder)
{
	pthread_mutex_unlock(coder->self_mutex);
	pthread_mutex_unlock(coder->table->table_mutex);
	log_msg("burned out", coder->table, coder->number);
	pthread_mutex_lock(coder->table->table_mutex);
	coder->table->dead_coder = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
}
