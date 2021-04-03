/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:31:06 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/03 14:43:47 by moharras         ###   ########.fr       */
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

// char			*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char		*ab;
// 	size_t		i;

// 	i = 0;
// 	if (s == 0)
// 		return (NULL);
// 	if (start > len)
// 		return (ft_strdup(""));
// 	ab = (char *)malloc((len + 1) * sizeof(char));
// 	if (ab == NULL)
// 		return (NULL);
// 	while (s[start + i] && i < len)
// 	{
// 		ab[i] = s[start + i];
// 		i++;
// 	}
// 	ab[i] = '\0';
// 	return (ab);
// }