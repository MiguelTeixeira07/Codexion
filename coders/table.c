/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 17:07:25 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/16 18:22:41 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

int	table_push(t_table *self, int coder)
{
	static int	num_coders = 0;
	t_coder		*new;

	if (init_coder(self, &new, coder))
		return (-1);
	pthread_mutex_lock(self->table_mutex);
	if (!num_coders)
	{
		pthread_mutex_unlock(self->table_mutex);
		num_coders++;
		return (first_coder(self, new));
	}
	new->prev = self->last;
	new->next = self->first;
	new->left_dongle = new->prev->right_dongle;
	new->prev->next = new;
	self->first->prev = new;
	self->first->left_dongle = new->right_dongle;
	self->last = new;
	pthread_mutex_unlock(self->table_mutex);
	num_coders++;
	return (0);
}
