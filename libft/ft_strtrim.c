/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:14:25 by moharras          #+#    #+#             */
/*   Updated: 2019/11/10 16:27:15 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_exist(char const *set, char s)
{
	size_t		i;
	char		*p_set;

	i = 0;
	p_set = (char*)set;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		l;
	size_t		k;

	i = 0;
	j = 0;
	l = 1;
	if (!s1 || !set)
		return (NULL);
	while (ft_is_exist(set, *(s1 + i)))
		i++;
	k = ft_strlen(s1);
	while (k - l > i && ft_is_exist(set, *(s1 + ft_strlen(s1) - l)))
	{
		j++;
		l++;
	}
	return (ft_substr(s1, i, ft_strlen(s1) - i - j));
}
