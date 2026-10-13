/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:04 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/12 17:40:39 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int main(int argc, char **argv)
{
	t_args	args;
	int		result;

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
	result = start_simulation(&args);
	if (result == -1)
		printf("Bad ending 2. Malloc fail.");
	if (result == 1)
		printf("Good ending. Every coder reached compile goal.");
	if (result == 2)
		printf("Bad ending 1. One or more coders died.");
	gar_col(DUMP, 0);
	return 0;
}
