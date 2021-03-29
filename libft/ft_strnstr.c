/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 15:57:29 by moharras          #+#    #+#             */
/*   Updated: 2019/11/09 18:48:07 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	char			*p_hay;
	char			*p_needle;
	size_t			i;
	size_t			j;

	j = 0;
	i = 0;
	p_hay = (char*)hay;
	p_needle = (char*)needle;
	if (!*p_needle || (len == 0 && !hay))
		return (p_hay);
	while (p_hay[i] && i < len)
	{
		j = 0;
		while (p_needle[j] != '\0' &&
				p_needle[j] == p_hay[i + j] && i + j < len)
			j++;
		if (p_needle[j] == '\0')
			return (p_hay + i);
		i++;
	}
	return (0);
}
