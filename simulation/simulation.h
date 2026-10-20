/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:22:03 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/20 16:42:49 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIMULATION_H
# define SIMULATION_H

# include "../codexion.h"

// simulation.c
int 	start_simulation(struct s_args *args);
int     check_end(struct s_table *table);
void    *monitor_routine(void *args);

// monitor_helpers.c
void	update_queue(struct s_queue *queue, struct s_table *table);
void	allow_compiles(struct s_queue *queue);
void	wait_for_start(struct s_table *table);
void	update_end(struct s_table *table);

#endif