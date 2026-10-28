/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:10 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/28 20:03:49 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "../simulation/simulation.h"
#include "../garbage_collector/garbage_collector.h"

void	*coder(void *coder_info)
{
	t_coder	*coder;

	coder = (t_coder *)coder_info;
	pthread_mutex_lock(coder->table->table_mutex);
	pthread_cond_wait(coder->table->condition, coder->table->table_mutex);
	pthread_mutex_unlock(coder->table->table_mutex);
	while (1)
		if (compile(coder) || check_end(coder->table)
			|| debug_and_refactor(coder))
			break ;
	pthread_mutex_lock(coder->self_mutex);
	coder->waiting = 0;
	coder->compiling = 0;
	coder->in_queue = 0;
	coder->has_finished = 1;
	pthread_mutex_unlock(coder->self_mutex);
	pthread_mutex_lock(coder->table->table_mutex);
	coder->table->terminated_coders++;
	pthread_mutex_unlock(coder->table->table_mutex);
	return (NULL);
}

void	wake_em_up(t_table *table)
{
	pthread_mutex_lock(table->table_mutex);
	pthread_cond_broadcast(table->condition);
	pthread_mutex_unlock(table->table_mutex);
}

int	create_threads(t_table *table, pthread_t *monitor)
{
	t_coder	*curr;
	int		i;

	curr = table->first;
	i = 0;
	monitor = gar_col(ALLOC, sizeof(pthread_t));
	if (!monitor)
		return (-1);
	pthread_create(monitor, NULL, &monitor_routine, table);
	while (++i <= table->args->num_coders)
	{
		pthread_create(curr->thread, NULL, &coder, curr);
		curr = curr->next;
	}
	curr = table->first;
	i = 0;
	usleep(1000000);
	wake_em_up(table);
	pthread_join(*monitor, NULL);
	while (++i <= table->args->num_coders)
	{
		pthread_join(*curr->thread, NULL);
		curr = curr->next;
	}
	return (0);
}

void	destroy_everything(t_table *table)
{
	int		i;
	t_coder *coder;

	i = 0;
	coder = table->first;
	while (++i <= table->args->num_coders)
	{
		pthread_mutex_destroy(coder->self_mutex);
		pthread_cond_destroy(coder->condition);
		pthread_mutex_destroy(coder->left_dongle->dongle);
		coder = coder->next;
	}
	pthread_mutex_destroy(table->table_mutex);
	pthread_mutex_destroy(table->log_mutex);
	pthread_cond_destroy(table->condition);
}
