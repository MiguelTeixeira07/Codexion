/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:16:41 by migteixe          #+#    #+#             */
/*   Updated: 2026/09/30 19:17:33 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	outsize(int n)
{
	int	size;

	size = (n <= 0);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		size;
	char	*out;

	nb = n;
	size = outsize(n);
	out = malloc(size + 1);
	if (!out)
		return (NULL);
	out[size] = '\0';
	if (n == 0)
		out[0] = '0';
	if (n < 0)
	{
		nb = -nb;
		out[0] = '-';
	}
	while (nb > 0)
	{
		out[--size] = '0' + (nb % 10);
		nb /= 10;
	}
	return (out);
}
