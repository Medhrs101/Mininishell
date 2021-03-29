/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:28:16 by moharras          #+#    #+#             */
/*   Updated: 2019/11/09 19:13:35 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	i = 0;
	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	if ((!s1 || !s2) && n == 0)
		return (0);
	while (p_s1[i] == p_s2[i] && p_s1[i] && p_s2[i] && i + 1 < n)
		i++;
	if (i == n)
		return (0);
	return (p_s1[i] - p_s2[i]);
}
