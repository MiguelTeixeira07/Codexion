/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:10 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/08 19:41:37 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "../simulation/simulation.h"


void	*coder(void *coder_info)
{
	t_coder	*coder;

	coder = (t_coder *)coder_info;
	pthread_mutex_lock(coder->self_mutex);
	pthread_cond_wait(coder->table_condition, coder->self_mutex);
	pthread_mutex_unlock(coder->self_mutex);
	while (1)
	{
		compile(coder);
		debug_and_refactor(coder);
	}
	return (NULL);
}

void	wake_em_up(t_table *table)
{
	pthread_mutex_lock(table->table_mutex);
	pthread_cond_broadcast(table->condition);
	pthread_mutex_unlock(table->table_mutex);
}

void	create_threads(t_table *table, pthread_t *monitor) {
	t_coder	*curr;
	int		i;

	curr = table->first;
	i = 0;
	monitor = gar_col(ALLOC, sizeof(pthread_t));
	if (!monitor)
		return ;
	pthread_create(monitor, NULL, &monitor_routine, table);
	while(++i <= table->num_coders)
	{
		pthread_create(curr->thread, NULL, &coder, curr);
		curr = curr->next;
	}
	curr = table->first;
	i = 0;
	wake_em_up(table);
	pthread_join(*monitor, NULL);
	while (++i <= table->num_coders)
	{
		pthread_join(*curr->thread, NULL);
		curr = curr->next;
	}
}
