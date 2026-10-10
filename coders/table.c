/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 17:07:25 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/10 17:07:45 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


int	table_push(t_table *self, int coder) {
	t_coder	*new;

	self->num_coders++;
	if (init_coder(self, &new, coder))
		return (-1);
	pthread_mutex_lock(self->table_mutex);
	if (self->num_coders == 1) {
		pthread_mutex_unlock(self->table_mutex);
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
	return (0);
}
