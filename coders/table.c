/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 17:07:25 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/04 18:50:12 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


static int	first_coder(t_table *self, t_coder *new)
{
	self->first = new;
	self->last = new;
	new->prev = new;
	new->next = new;
	new->left_dongle = new->right_dongle;
	return (0);
}

static int	init_coder(t_coder *new, t_args *args, int coder)
{
	new = gar_col(ALLOC, sizeof(t_coder));
	if (!new)
		return (1);
	new->thread = gar_col(ALLOC, sizeof(pthread_t));
	if (!new->thread)
		return (1);
	new->number = coder;
	new->self_mutex = gar_col(ALLOC, sizeof(pthread_mutex_t));
	if (!new->self_mutex)
		return (1);
	pthread_mutex_init(new->self_mutex, NULL);
	new->last_compile_start = 0;
	new->compile_ammount = 0;
	new->right_dongle = gar_col(ALLOC, sizeof(pthread_mutex_t));
	if (!new->right_dongle)
		return (1);
	pthread_mutex_init(new->right_dongle, NULL);
	new->prog_args = args;
	return (0);
}

int	table_push(t_table *self, t_args *args, int coder) {
	t_coder	*new;

	self->num_coders++;
	if (init_coder(new, coder, args))
		return (1);
	if (self->num_coders == 1)
		return (first_coder(self, new));
	new->prev = self->last;
	new->next = self->first;
	new->left_dongle = new->prev->right_dongle;
	new->prev->next = new;
	self->first->prev = new;
	self->first->left_dongle = new->right_dongle;
	self->last = new;
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
	pthread_mutex_init(table->table_mutex, NULL);
	return table;
}
