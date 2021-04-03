/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:08:28 by ymarji            #+#    #+#             */
/*   Updated: 2019/10/23 16:51:37 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	myc;
	char	*str;
	int		len;

	str = (char *)s;
	myc = (char)c;
	len = (int)ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == myc)
			return (str + len);
		--len;
	}
	return (NULL);
}
