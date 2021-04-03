/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:17:03 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/23 14:56:49 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*dst_str;
	char	*src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	i = 0;
	if (src_str < dst_str)
	{
		while (len > 0)
		{
			dst_str[len - 1] = src_str[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(dst_str, src_str, len);
	}
	return (dst);
}
