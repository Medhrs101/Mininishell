/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:30:27 by moharras          #+#    #+#             */
/*   Updated: 2019/10/26 19:18:42 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p_dst;
	unsigned char		*p_src;
	size_t				i;

	i = len;
	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	if (src == dst)
		return (dst);
	if (p_src < p_dst)
	{
		while (len-- > 0)
		{
			p_dst[len] = p_src[len];
		}
	}
	else
		ft_memcpy(p_dst, p_src, len);
	return (dst);
}
