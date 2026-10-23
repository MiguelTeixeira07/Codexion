/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:57:03 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/23 17:17:17 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../garbage_collector/garbage_collector.h"

char	*ft_strdup(const char *s) {
	char	*dest;
	int		i;

	dest = gar_col(ALLOC, (strlen((char *)s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

__time_t gettime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return -1;
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_msg(char *str, t_table *table, int coder_num)
{
	__time_t	now;

	pthread_mutex_lock(table->table_mutex);
	if (!(table->finished == table->args->num_coders || table->dead_coder))
	{
		pthread_mutex_lock(table->log_mutex);
		now = gettime();
		printf("%ld %d %s\n", now - table->sim_start, coder_num, str);
		pthread_mutex_unlock(table->log_mutex);
	}
	pthread_mutex_unlock(table->table_mutex);
}

