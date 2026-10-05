/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:05:11 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/30 20:21:01 by migteixe         ###   ########.fr       */
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
		printf("%s ", node->coder->number);
		node = node->next;
	}
	printf("| Back\n");
}

void	queue_pop(t_queue **self)
{
	t_node	*remove;

	if ((*self)->top == (*self)->bottom)
	{
		(*self)->top = NULL;
		(*self)->bottom = NULL;
		return;
	}
	remove = (*self)->bottom;
	if(remove->previous)
	{
		(*self)->bottom = remove->previous;
		printf("%s\n", remove->coder);
		remove = NULL;
		(*self)->bottom->next = NULL;
	}
	else
		(*self)->bottom = NULL;
}
