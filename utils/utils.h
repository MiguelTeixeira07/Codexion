/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migteixe <migteixe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:57:09 by migteixe          #+#    #+#             */
/*   Updated: 2026/10/12 22:06:04 by migteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../codexion.h"


char	*ft_strdup(const char *s);
char	*itoa(int n);
int		ft_isdigit(char c);
__time_t gettime(void);
void    log_msg(char *str, pthread_mutex_t *log_mutex, int coder_num);

#endif