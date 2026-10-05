/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:56 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/02 21:35:18 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include "../coders/coders.h"


typedef struct s_node
{
	t_coder			*coder;
	struct s_node	*previous;
	struct s_node	*next;
} t_node;

typedef struct s_queue
{
	t_node	*top;
	t_node	*bottom;
} t_queue;


t_queue	*init_queue();
void	queue_push(t_queue **self, t_coder *coder, char *scheduler);
void	queue_pop(t_queue **self);
void	print_queue(t_queue *self);
