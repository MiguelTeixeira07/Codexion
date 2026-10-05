/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:08 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/04 17:14:24 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include "../garbage_collector/garbage_collector.h"
#include "../parsing/parser.h"


typedef struct s_coder {
	pthread_t		*thread;
	pthread_mutex_t	*self_mutex;
	int				number;
	int				last_compile_start;
	int				compile_ammount;
	pthread_mutex_t	*left_dongle;
	pthread_mutex_t	*right_dongle;
	struct s_coder	*next;
	struct s_coder	*prev;
	t_args			*prog_args;
} t_coder;

typedef struct s_table {
	t_coder			*first;
	t_coder			*last;
	pthread_mutex_t	*table_mutex;
	int				num_coders;
} t_table;

//actions.c
void	compile(t_coder *args);
void	debug(t_coder *args);
void	refactor(t_coder *args);

//coders.c
t_table	*init_table();
int		table_push(t_table *self, t_args *args, int coder);
void	*coder(void *coder_info);
void	create_threads(t_table *table);
