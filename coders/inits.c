/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 22:18:44 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:24:28 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


int	first_coder(t_table *self, t_coder *new)
{
	self->first = new;
	self->last = new;
	new->prev = new;
	new->next = new;
	new->left_dongle = new->right_dongle;
	return (0);
}

static int	coder_allocs(t_coder **new)
{
	*new = gar_col(ALLOC, sizeof(t_coder));
	if (!new)
		return (1);
	(*new)->thread = gar_col(ALLOC, sizeof(pthread_t));
	if (!(*new)->thread)
		return (1);
	(*new)->self_mutex = gar_col(ALLOC, sizeof(pthread_mutex_t));
	if (!(*new)->self_mutex)
		return (1);
	(*new)->table_mutex = gar_col(ALLOC, sizeof(pthread_mutex_t));
	if (!(*new)->table_mutex)
		return (1);
	(*new)->condition = gar_col(ALLOC, sizeof(pthread_cond_t));
	if (!(*new)->condition)
		return (1);
	(*new)->right_dongle = gar_col(ALLOC, sizeof(pthread_mutex_t));
	if (!(*new)->right_dongle)
		return (1);
	pthread_mutex_init((*new)->self_mutex, NULL);
	pthread_mutex_init((*new)->self_mutex, NULL);
	pthread_mutex_init((*new)->right_dongle, NULL);
	pthread_cond_init((*new)->condition, NULL);
	return (0);
}

int	init_coder(t_table *table, t_coder **new, t_args *args, int coder)
{
	if (coder_allocs(new))
		return (1);
	(*new)->table_condition = table->condition;
	(*new)->number = coder;
	(*new)->last_compile_start = 0;
	(*new)->compile_ammount = 0;
	(*new)->waiting = 0;
	(*new)->compiling = 0;
	(*new)->prog_args = args;
	return (0);
}

t_table	*init_table()
{
	t_table *table;

	table = gar_col(ALLOC, sizeof(t_table));
	if (!table)
		return (NULL);
	table->first = NULL;
	table->last = NULL;
	table->num_coders = 0;
	table->table_mutex = gar_col(ALLOC, sizeof(pthread_mutex_t));
	if (!table->table_mutex)
		return (NULL);
	table->condition = gar_col(ALLOC, sizeof(pthread_cond_t));
	pthread_mutex_init(table->table_mutex, NULL);
	return table;
}
