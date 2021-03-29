/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:01:21 by moharras          #+#    #+#             */
/*   Updated: 2021/02/25 08:24:51 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_strcpy1(char *dest, char *src)
{
	int			i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void			ft_strcat1(char *dest, char *src)
{
	int			len;
	int			i;

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

char			*ft_strjoin1(char const *s1, char const *s2)
{
	size_t		len_total;
	char		*join;

	if (!s1 || !s2)
		return (NULL);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	while (!(join = (char *)malloc(sizeof(char) * (len_total + 1))))
		return (NULL);
	ft_strcpy1(join, (char*)s1);
	ft_strcat1(join, (char*)s2);
	return (join);
}

char			*ft_strdup1(const char *s1)
{
	int			i;
	char		*s;
	char		*p_s1;
	int			len;

	i = 0;
	len = 0;
	p_s1 = (char*)s1;
	while (p_s1[len])
		len++;
	if (!p_s1 || !(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (p_s1[i])
	{
		s[i] = p_s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
