/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:04 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/04 15:49:28 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector/garbage_collector.h"
#include "queue/queue.h"
#include "utils/utils.h"
#include "coders/coders.h"
#include "parsing/parser.h"
#include "simulation/simulation.h"


int main(int argc, char **argv)
{
	t_table	*table;
	t_args	args;
	int		num_coders;

	if(argc != 9)
	{
		printf("Expected 8 arguments\n");
		return 0;
	}
	if (parse(&argv[1], &args))
	{
		printf("Parsing error\n");
		return 0;
	}
	start_simulation(&args);
	gar_col(DUMP, 0);
	return 0;
}
