/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:51:43 by moharras          #+#    #+#             */
/*   Updated: 2019/11/08 15:54:42 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			len_dst;
	size_t			len_src;
	size_t			i;
	size_t			l;

	i = 0;
	if (size == 0 && dst == NULL)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	l = len_dst;
	if (len_dst >= size)
		return (len_src + size);
	while (src[i] && len_dst + 1 < size)
	{
		dst[len_dst++] = (char)src[i];
		i++;
	}
	dst[len_dst] = '\0';
	return (l + len_src);
}
