/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 15:53:53 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/20 02:20:09 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../codexion.h"
#include "../coders/coders.h"
#include "../utils/utils.h"

static int	ft_atoi(char *str)
{
	unsigned int	num;
	int				i;

	num = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	return (num);
}

static int	only_integer(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

static int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (str1[i] == str2[i]);
}

static void	assign_vals(int *vals, t_args *args)
{
	args->num_coders = vals[0];
	args->time_to_burnout = vals[1];
	args->time_to_compile = vals[2];
	args->time_to_debug = vals[3];
	args->time_to_refactor = vals[4];
	args->num_compiles = vals[5];
	args->dongle_cooldown = vals[6];
}

int	parse(char **args, t_args *output)
{
	int	vals[7];
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!only_integer(args[i]))
			return (1);
		vals[i] = ft_atoi(args[i]);
		if (vals[i] < 1)
			return (1);
		i++;
	}
	if (!ft_strcmp(args[i], "fifo") && !ft_strcmp(args[i], "edf"))
		return (1);
	assign_vals(vals, output);
	output->scheduler = args[i];
	return (0);
}
