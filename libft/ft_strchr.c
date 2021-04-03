/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:51:53 by ymarji            #+#    #+#             */
/*   Updated: 2019/11/04 08:56:34 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	myc;
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	myc = (char)c;
	while (s[i])
	{
		if (str[i] == myc)
			return (str + i);
		i++;
	}
	if (str[i] == myc)
		return (str + i);
	return (NULL);
}
