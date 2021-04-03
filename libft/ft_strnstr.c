/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 13:35:12 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/21 18:52:32 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)haystack;
	j = 0;
	i = 0;
	if (ft_strlen(needle) == 0)
		return (str);
	while (str[i] && i < (int)len)
	{
		if (str[i] == needle[0])
		{
			j = 1;
			while (str[i + j] == needle[j] && i + j < (int)len && needle[j])
				j++;
			if (needle[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (0);
}
