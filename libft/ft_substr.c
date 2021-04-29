/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:31:06 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/29 14:27:37 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	calculate_len_s(size_t len, size_t len_s, unsigned int start)
{
	if (len > (len_s - start))
		len = len_s - start;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		len_s;
	char		*sub;
	char		*p_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	p_s = (char *)s;
	i = 0;
	if (len_s < start)
		return (ft_strdup(""));
	calculate_len_s(len, len_s, start);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && p_s[i + start])
	{
		sub[i] = p_s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
