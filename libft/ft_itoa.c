/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:28:46 by moharras          #+#    #+#             */
/*   Updated: 2019/10/26 21:29:33 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lengthnumber(int n)
{
	int				count;

	count = 0;
	if (n <= 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	long			nb;
	int				len_number;
	char			*t;

	nb = n;
	len_number = ft_lengthnumber(nb);
	if (!(t = (char *)malloc(sizeof(char) * (len_number + 1))))
		return (NULL);
	t[len_number] = '\0';
	len_number--;
	if (nb < 0)
		nb = -nb;
	while (len_number >= 0)
	{
		t[len_number] = (nb % 10) + '0';
		nb = nb / 10;
		len_number--;
	}
	if (n < 0)
		t[0] = '-';
	return (t);
}
