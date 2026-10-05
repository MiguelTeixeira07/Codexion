/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:02 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/04 18:48:14 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "../coders/coders.h"


int	check_end(t_table *table)
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
}

void	*monitor(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	while (table->finished < table->num_coders)
		check_end(table);
	
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
	while (++i < args->num_coders)
		if (table_push(table, args, i))
			return ;
	pthread_create(monitor, NULL, &monitor, table);
	create_threads(table);
	return ;
}
