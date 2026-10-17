/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:04 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/17 22:24:45 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int main(int argc, char **argv)
{
	t_args	args;

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
