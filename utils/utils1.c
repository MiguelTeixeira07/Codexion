/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:57:03 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/30 19:17:47 by migteixe         ###   ########.fr       */
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

void	log_msg(char *str, pthread_mutex_t *log_mutex, int coder_num)
{
	pthread_mutex_lock(log_mutex);
	printf("%d %s\n", coder_num, str);
	pthread_mutex_unlock(log_mutex);
}

