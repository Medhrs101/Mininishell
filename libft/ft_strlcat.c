/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 10:36:00 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/22 11:41:54 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lent;
	int		i;

	i = 0;
	lent = ft_strlen(dst);
	while (src[i] && i < (int)(size - lent - 1) && size > lent)
	{
		dst[lent + i] = src[i];
		i++;
	}
	if (size > lent)
	{
		dst[lent + i] = '\0';
		return (lent + ft_strlen(src));
	}
	return (size + ft_strlen(src));
}
