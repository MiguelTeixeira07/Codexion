/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:52 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/19 19:52:06 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

static void	queue_fifo_push(t_queue *self, t_coder *coder)
{
	t_node	*new;

	new = gar_col(ALLOC, sizeof(t_node));
	if (!new)
		return ;
	new->coder = coder;
	new->next = NULL;
	new->previous = self->bottom;
	if (!self->top)
		self->top = new;
	else
		self->bottom->next = new;
	self->bottom = new;
}

static void	swap_with_previous(t_queue *queue, t_node *node)
{
	t_node	*prev;
	t_node	*before_prev;
	t_node	*next;

	prev = node->previous;
	before_prev = prev->previous;
	next = node->next;
    if (!queue->top || !node || !node->previous)
        return ;
    if (before_prev)
        before_prev->next = node;
    else
        queue->top = node;
    node->previous = before_prev;
    node->next = prev;
    prev->previous = node;
    prev->next = next;
    if (next)
        next->previous = prev;
}

void	queue_push(t_queue *self, t_coder *coder, char *scheduler)
{
	t_node	*curr;

	curr = self->bottom;
	queue_fifo_push(self, coder);
	if (strcmp(scheduler, "edf"))
		while (curr && curr->previous && curr->previous->coder->last_compile_start > curr->coder->last_compile_start)
		{
			swap_with_previous(self, curr);
			curr = curr->previous;
		}
}
