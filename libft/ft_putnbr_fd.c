/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:16:18 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/26 15:59:31 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		div;
	int		i;
	long	l_n;

	l_n = n;
	i = 0;
	div = 1;
	if (l_n < 0)
	{
		l_n *= -1;
		ft_putchar_fd('-', fd);
	}
	while (l_n / div > 9)
		div *= 10;
	while (div > 9)
	{
		ft_putchar_fd((l_n / div) + '0', fd);
		l_n %= div;
		div /= 10;
	}
	ft_putchar_fd(l_n + '0', fd);
}
