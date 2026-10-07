/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:41 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:18:41 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "../codexion.h"

typedef struct s_garbage {
    void *garbage;
    struct s_garbage *next;
} t_garbage;

void *gar_col(int action, size_t bytes);

#endif