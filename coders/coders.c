/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:10 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/20 01:42:54 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


void	*coder(void *param_args)
{
	t_coder_args	*args;

	args = (t_coder_args *)param_args;
	compile(param_args);
	debug(param_args);
	refactor(param_args);
}

t_table	*init_table()
{
	t_table *table;

	table = gar_col(ALLOC, sizeof(t_table));
	if (!table)
		return NULL;
	table->first = NULL;
	table->last = NULL;
	return table;
}

void	table_push(t_table **self, int coder) {
	t_coder	*new;

	new = gar_col(ALLOC, sizeof(t_coder));
	new->number = coder;
	new->right_dongle = gar_col(ALLOC, sizeof(pthread_mutex_t));
	pthread_mutex_init(new->right_dongle, NULL);
	if (!(*self)->first)
	{
		(*self)->first = new;
		(*self)->last = new;
		new->next = new;
		new->prev = new;
		new->right_dongle = new->right_dongle;
		new->left_dongle = new->right_dongle;
	}
	else
	{
		new->prev = (*self)->last;
		new->next = (*self)->first;
		new->left_dongle = new->prev->right_dongle;
		(*self)->first->left_dongle = new->right_dongle;
		(*self)->last->next = new;
		(*self)->first->prev = new;
		(*self)->last = new;
	}
}

void	create_threads(t_table *table) {
	t_coder			*curr;
	t_coder_args	*args;

	curr = table->first;
	do
	{
		pthread_create(&curr->thread, NULL, &coder, args);
		curr = curr->next;
	} while(curr != table->first);
	printf("\n");
	do {
		pthread_join(curr->thread, NULL);
		curr = curr->next;
	} while(curr != table->first);
}
