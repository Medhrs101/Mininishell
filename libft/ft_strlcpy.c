/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 08:54:09 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/26 13:32:10 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		lent;

	i = 0;
	if (dst == NULL)
		return (0);
	lent = ft_strlen(src);
	while ((int)i < (int)size - 1 && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	if (size > 0)
		dst[i] = '\0';
	return (lent);
}
