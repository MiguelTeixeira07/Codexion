/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 17:51:18 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/20 01:08:26 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_args
{
	int		num_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		num_compiles;
	int		dongle_cooldown;
	char	*scheduler;
} t_args;

int	parse(char **args, t_args *output);
