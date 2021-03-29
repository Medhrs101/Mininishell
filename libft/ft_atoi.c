/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:06:40 by moharras          #+#    #+#             */
/*   Updated: 2019/11/08 15:58:33 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_atoi(const char *str)
{
	int				i;
	unsigned int	nb;
	int				signe;

	i = 0;
	nb = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '\0')
		return (0);
	else if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	return ((int)nb * signe);
}
