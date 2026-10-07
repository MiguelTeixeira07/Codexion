/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:57:09 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/07 23:15:32 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../codexion.h"


char	*ft_strdup(const char *s);
char	*itoa(int n);
size_t	ft_strlen(char *str);
int		ft_isdigit(char c);
int 	ft_strcmp(char *str1, char *str2);

#endif