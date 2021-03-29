/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 23:17:33 by moharras          #+#    #+#             */
/*   Updated: 2019/10/26 21:18:06 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	ft_strcat(char *dest, char *src)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (dest[len] != '\0')
		len++;
	while (src[i] != '\0')
	{
		dest[len] = src[i];
		len++;
		i++;
	}
	dest[len] = '\0';
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len_total;
	char			*join;

	if (!s1 || !s2)
		return (NULL);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	while (!(join = (char *)malloc(sizeof(char) * (len_total + 1))))
		return (NULL);
	ft_strcpy(join, (char*)s1);
	ft_strcat(join, (char*)s2);
	return (join);
}
