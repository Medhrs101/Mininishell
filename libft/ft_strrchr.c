/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 23:59:45 by moharras          #+#    #+#             */
/*   Updated: 2019/10/20 22:47:21 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	p_c;
	char			*p_s;
	int				i;
	int				count;

	i = 0;
	p_s = (char*)s;
	p_c = (char)c;
	while (p_s[i])
		i++;
	count = i;
	while (i-- > 0)
		if (p_s[i] == p_c)
			return (p_s + i);
	if (p_s[count] == '\0' && c == '\0')
		return (p_s + count);
	return (NULL);
}
