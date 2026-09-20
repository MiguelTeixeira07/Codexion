/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:04 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/20 02:22:06 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector/garbage_collector.h"
#include "queue/queue.h"
#include "utils/utils.h"
#include "coders/coders.h"
#include "parsing/parser.h"


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
	//start_simulation(&args);
	printf(
		"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n",
		args.num_coders,
		args.time_to_burnout,
		args.time_to_compile,
		args.time_to_debug,
		args.time_to_refactor,
		args.num_compiles,
		args.dongle_cooldown,
		args.scheduler
	);
	//gar_col(DUMP, 0);
	return 0;
}
