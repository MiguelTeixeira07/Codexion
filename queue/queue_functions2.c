/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:05:11 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:30:07 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"


t_queue	*init_queue()
{
	t_queue	*queue;

	queue = gar_col(ALLOC, sizeof(t_queue));
	if (!queue)
		return NULL;
	queue->top = NULL;
	queue->bottom = NULL;
	return queue;
}

void	print_queue(t_queue *self)
{
	t_node	*node;

	if(!self->top)
	{
		printf("Queue is empty\n");
		return;
	}
	node = self->top;
	printf("Front | ");
	while(node)
	{
		printf("%d ", node->coder->number);
		node = node->next;
	}
	printf("| Back\n");
}

void	queue_remove(t_queue *self, t_node *target)
{
	t_node	*remove;

	if (self->top == self->bottom)
	{
		self->top = NULL;
		self->bottom = NULL;
		return;
	}
	remove = self->top;
	while (remove->next && remove->coder->number != target->coder->number)
		remove = remove->next;
	if (!remove)
		return ;
	if (!remove->next)
		self->bottom = remove->previous;
	remove->previous->next = remove->next;
	remove = NULL;
}
