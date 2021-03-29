/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 23:49:03 by moharras          #+#    #+#             */
/*   Updated: 2019/11/10 11:52:58 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int			i;
	char		*s;
	int			len;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[i])
	{
		s[i] = (char)s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
