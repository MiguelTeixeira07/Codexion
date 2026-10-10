/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:56 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:15:13 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "../coders/coders.h"
# include "../codexion.h"


typedef struct s_node
{
	t_coder			*coder;
	int				n_compiles;
	struct s_node	*previous;
	struct s_node	*next;
} t_node;

typedef struct s_queue
{
	t_node	*top;
	t_node	*bottom;
} t_queue;


t_queue	*init_queue();
void	queue_push(t_queue *self, t_coder *coder, char *scheduler);
void	queue_remove(t_queue *self, t_node *coder);
void	print_queue(t_queue *self);

#endif