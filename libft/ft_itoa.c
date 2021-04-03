/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:10:46 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/26 13:25:58 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*put_char(char *str, int cp, long n, int sign)
{
	if (n < 0)
		n *= -1;
	str[cp] = '\0';
	while (cp > 0)
	{
		str[cp - 1] = n % 10 + '0';
		n = n / 10;
		cp--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	teg;
	int		cp;

	cp = 0;
	teg = n;
	size = 0;
	if (teg < 0)
	{
		teg *= -1;
		size = 1;
	}
	while (teg / 10 > 0)
	{
		teg = teg / 10;
		cp++;
	}
	cp = cp + 2 + size;
	str = (char *)malloc(sizeof(char) * (cp));
	if (str == NULL)
		return (NULL);
	str = put_char(str, cp - 1, (long)n, size);
	return (str);
}
