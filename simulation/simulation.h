/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:22:03 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:14:49 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIMULATION_H
# define SIMULATION_H

# include "../parsing/parser.h"
# include "../coders/coders.h"
# include "../queue/queue.h"

void	start_simulation(t_args *args);
void    *monitor_routine(void *args);

#endif