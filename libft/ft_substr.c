/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 23:09:41 by moharras          #+#    #+#             */
/*   Updated: 2019/11/01 13:10:51 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			len_s;
	char			*sub;
	char			*p_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	p_s = (char *)s;
	i = 0;
	if (len_s < start)
		return (ft_strdup(""));
	len = (len > (len_s - start)) ? (len_s - start) : len;
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && p_s[i + start])
	{
		sub[i] = p_s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
