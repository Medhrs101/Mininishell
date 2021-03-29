/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:51:34 by moharras          #+#    #+#             */
/*   Updated: 2019/10/26 21:02:24 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			len;
	int			i;
	char		*tab;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(tab = (char *)malloc((sizeof(char) * (len + 1)))))
		return (NULL);
	tab[len] = '\0';
	while (i < len)
	{
		tab[i] = (*f)(i, s[i]);
		i++;
	}
	return (tab);
}
