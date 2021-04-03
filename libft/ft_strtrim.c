/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:05:13 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/26 13:45:52 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check(char c, char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		j;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	str = ft_strdup(s1);
	if (str == NULL)
		return (NULL);
	j = 0;
	while (check(str[0], (char *)set) == 1)
		str++;
	len = ft_strlen(str) - 1;
	while (len > 0 && check(str[len], (char *)set))
		len--;
	return (ft_substr(str, 0, len + 1));
}
