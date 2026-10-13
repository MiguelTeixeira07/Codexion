/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:29:28 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/12 17:29:31 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>


#ifndef CODEXION_H
# define CODEXION_H

# define DUMP 2
# define ALLOC 1
# define INT_MAX 2147483647

struct s_args;
struct s_table;
struct s_coder;
struct s_node;
struct s_queue;

# include "garbage_collector/garbage_collector.h"
# include "parsing/parser.h"
# include "coders/coders.h"
# include "queue/queue.h"
# include "simulation/simulation.h"
# include "utils/utils.h"

#endif