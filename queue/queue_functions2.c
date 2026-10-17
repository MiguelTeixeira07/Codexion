/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:05:11 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/17 20:59:10 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = gar_col(ALLOC, sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->top = NULL;
	queue->bottom = NULL;
	return (queue);
}

void	print_queue(t_queue *self)
{
	t_node	*node;

	if (!self->top)
	{
		printf("Queue is empty\n");
		return ;
	}
	node = self->top;
	printf("Front | ");
	while (node)
	{
		printf("%d ", node->coder->number);
		node = node->next;
	}
	printf("| Back\n");
}

t_node	*queue_remove(t_queue *self, t_node *target)
{
	t_node	*out;

	if (!self || !target)
		return (NULL);
	out = target->next;
	if (target == self->top)
		self->top = target->next;
	if (target == self->bottom)
		self->bottom = target->previous;
	if (target->previous)
		target->previous->next = target->next;
	if (target->next)
		target->next->previous = target->previous;
	target->next = NULL;
	target->previous = NULL;
	return (out);
}
