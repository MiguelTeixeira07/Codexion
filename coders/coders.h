/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:08 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/28 18:43:42 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include "../codexion.h"

struct	s_table;

typedef struct s_dongle
{
	pthread_mutex_t	*dongle;
	__time_t		last_used;
}					t_dongle;

typedef struct s_coder
{
	pthread_t		*thread;
	pthread_mutex_t	*self_mutex;
	pthread_cond_t	*condition;
	int				number;
	int				waiting;
	int				compiling;
	int				in_queue;
	int				compile_ammount;
	int				has_finished;
	__time_t		last_compile_start;
	struct s_dongle	*left_dongle;
	struct s_dongle	*right_dongle;
	struct s_coder	*next;
	struct s_coder	*prev;
	struct s_table	*table;
}					t_coder;

typedef struct s_table
{
	t_coder			*first;
	t_coder			*last;
	pthread_mutex_t	*table_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_cond_t	*condition;
	int				finished;
	int				dead_coder;
	int				terminated_coders;
	int				coders_compiling;
	__time_t		sim_start;
	struct s_args	*args;
}					t_table;

//actions.c
int		compile(t_coder *args);
int		debug_and_refactor(t_coder *args);

//coders.c
void	*coder(void *coder_info);
int		create_threads(t_table *table, pthread_t *monitor);
void	destroy_everything(t_table *table);

//table.c
int		table_push(t_table *self, int coder);

//inits.c
int		first_coder(t_table *self, t_coder *new);
int		init_coder(t_table *table, t_coder **new, int coder);
t_table	*init_table(struct s_args *prog_args);

#endif