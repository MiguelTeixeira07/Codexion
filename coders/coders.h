/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:08 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/20 01:57:46 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include "../garbage_collector/garbage_collector.h"


typedef struct s_coder {
	pthread_t		thread;
	int				number;
	pthread_mutex_t	*left_dongle;
	pthread_mutex_t	*right_dongle;
	struct s_coder	*next;
	struct s_coder	*prev;
} t_coder;

typedef struct s_table {
	t_coder	*first;
	t_coder	*last;
} t_table;

typedef struct s_coder_args {
	t_coder *coder;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		dongle_cooldown;
	int		time_to_burnout;
} t_coder_args;

//actions.c
void	compile(t_coder_args *args);
void	debug(t_coder_args *args);
void	refactor(t_coder_args *args);

//coders.c
t_table	*init_table();
void	*coder(void *ptr);
void	create_threads(t_table *table);
