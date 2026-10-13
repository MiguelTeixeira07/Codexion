/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:05:11 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/12 18:25:12 by migteixe         ###   ########.fr       */
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

void	queue_remove(t_queue *self, t_node *target)
{
	t_node	*remove;

	if (self->top == self->bottom)
	{
		self->top = NULL;
		self->bottom = NULL;
		return ;
	}
	remove = target;
	if (!remove->next)
		self->bottom = remove->previous;
	else if (!remove->previous)
		self->top = remove->next;
	else
		remove->previous->next = remove->next;
	remove = NULL;
}
