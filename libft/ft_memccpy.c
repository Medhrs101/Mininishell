/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:53:37 by ymarji            #+#    #+#             */
/*   Updated: 2019/11/07 10:14:10 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*dst_str;
	unsigned char	*src_str;

	dst_str = (unsigned char *)dst;
	src_str = (unsigned char *)src;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		if (src_str[i] == uc)
			return ((void *)dst_str + i + 1);
		i++;
	}
	return (NULL);
}
