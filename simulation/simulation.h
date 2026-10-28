/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:22:03 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/28 18:43:06 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../codexion.h"
# include "../coders/coders.h"
# include "../queue/queue.h"
# include "../parsing/parser.h"

// simulation.c
int		start_simulation(t_table *table);
int		check_end(t_table *table);
void	*monitor_routine(void *args);

// monitor_helpers1.c
void	update_queue(t_queue *queue, t_table *table);
void	allow_compiles(t_queue *queue);
void	wait_for_start(t_table *table);
void	update_end(t_table *table);

// monitor_helpers2.c
void	order_compile(t_node *curr);
void	prepare_monitor(t_table *table, t_queue *queue);
void	burn_out(t_coder *coder);

#endif