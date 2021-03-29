/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:35:56 by moharras          #+#    #+#             */
/*   Updated: 2019/10/19 00:39:52 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	p_c;
	unsigned char	*p_s;
	size_t			i;

	i = 0;
	p_s = (unsigned char*)s;
	p_c = (unsigned char)c;
	while (i < n)
	{
		if (p_s[i] == p_c)
			return (&p_s[i]);
		i++;
	}
	return (NULL);
}
