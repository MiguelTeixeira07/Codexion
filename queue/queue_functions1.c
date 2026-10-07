/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:52 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:29:42 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "../garbage_collector/garbage_collector.h"
#include "../utils/utils.h"
#include "../coders/coders.h"



static void	queue_fifo_push(t_queue *self, t_coder *coder)
{
	t_node	*new;
	
	new = gar_col(ALLOC, sizeof(t_node));
	if(!new)
		return;
	new->coder = coder;
	new->n_compiles = coder->compile_ammount;
	new->previous = NULL;
	new->next = self->top;
	if (self->top)
		self->top->previous = new;
	else
		self->bottom = new;
	self->top = new;
}

/* static void	insert_first(t_queue *self, t_node *new)
{
	new->previous = self->bottom;
	if (self->bottom)
		self->bottom->next = new;
	else
	{
		self->top = new;
		self->bottom = new;
	}
}

static void	queue_edf_push(t_queue *self, t_coder *coder)
{
	t_node	*new;
	t_node	*curr;
	
	new = gar_col(ALLOC, sizeof(t_node));
	if(!new)
		return;
	new->coder = coder;
	new->n_compiles = coder->compile_ammount;
	new->next = NULL;
	new->previous = NULL;
	curr->next = self->top;
	//while (curr && curr->coder->deadline <= coder->deadline)
	//	curr = curr->next;
	if (!curr)
		insert_first(self, new);
	else
	{
		new->next = curr;
		new->previous = curr->previous;
		if (curr->previous)
		curr->previous->next = new;
		else
		self->top = new;
		curr->previous = new;
	}
} */

void	queue_push(t_queue *self, t_coder *coder, char *scheduler)
{
	if (ft_strcmp(scheduler, "fifo"))
		queue_fifo_push(self, coder);
	/*else
		queue_edf_push(self, coder);*/
}