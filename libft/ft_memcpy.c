/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:24:03 by moharras          #+#    #+#             */
/*   Updated: 2019/11/09 18:49:32 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*p_dst;
	const char		*p_src;
	size_t			i;

	i = 0;
	p_dst = (char*)dst;
	p_src = (const char*)src;
	if (src == dst)
		return (dst);
	if (!p_src && !p_dst)
		return (NULL);
	while (i < n)
	{
		p_dst[i] = p_src[i];
		i++;
	}
	return (dst);
}
