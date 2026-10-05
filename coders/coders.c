/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:56:10 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/04 17:23:43 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"


void	*coder(void *coder_info)
{
	t_coder	*coder;

	coder = (t_coder *)coder_info;
	while (coder->compile_ammount != coder->prog_args->num_compiles)
	{
		if (!pthread_mutex_lock(coder->left_dongle) && !pthread_mutex_lock(coder->right_dongle))
			compile(coder);
		pthread_mutex_lock(coder->self_mutex);
		coder->compile_ammount++;
		pthread_mutex_unlock(coder->self_mutex);
		pthread_mutex_unlock(coder->left_dongle);
		pthread_mutex_unlock(coder->right_dongle);
		debug(coder);
		refactor(coder);
	}
	return (NULL);
}

void	create_threads(t_table *table) {
	t_coder	*curr;
	int		i;

	curr = table->first;
	i = 0;
	while(++i <= table->num_coders)
	{
		pthread_create(curr->thread, NULL, &coder, curr);
		curr = curr->next;
	}
	curr = table->first;
	i = 0;
	while (++i <= table->num_coders)
	{
		pthread_join(*curr->thread, NULL);
		curr = curr->next;
	}
}
