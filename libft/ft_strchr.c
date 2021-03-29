/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 23:37:03 by moharras          #+#    #+#             */
/*   Updated: 2019/10/20 22:20:33 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		*p_s;
	char		p_c;
	int			i;

	i = 0;
	p_s = (char*)s;
	p_c = (unsigned char)c;
	while (p_s[i])
	{
		if (p_s[i] == p_c)
			return (p_s + i);
		i++;
	}
	if (p_s[i] == p_c)
		return (p_s + i);
	return (NULL);
}
