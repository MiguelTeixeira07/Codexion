/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:10 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/08 00:07:39 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"
#include "../simulation/simulation.h"


void	*coder(void *coder_info)
{
	t_coder	*coder;

	coder = (t_coder *)coder_info;
	printf("Coder %d here!\n", coder->number);
	pthread_mutex_lock(coder->self_mutex);
	printf("\n\ncoder %d locking the mutex\n\n", coder->number);
	pthread_cond_wait(coder->table_condition, coder->self_mutex);
	printf("\n\ncoder %d got access\n\n", coder->number);
	pthread_mutex_unlock(coder->self_mutex);
	printf("coder %d: I just woke up!\n", coder->number);
	while (1)
	{
		compile(coder);
		debug(coder);
		refactor(coder);
	}
	return (NULL);
}

void	wake_em_up(t_table *table)
{
	printf("About to wake these fuckers up!\n");
	pthread_mutex_lock(table->table_mutex);
	printf("In the process of waking these fuckers up...\n");
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
	pthread_join(*monitor, NULL);
	while (++i <= table->num_coders)
	{
		pthread_join(*curr->thread, NULL);
		curr = curr->next;
		usleep(10000);
	}
	printf("ts did not run before fs\n");
	wake_em_up(table);
}
