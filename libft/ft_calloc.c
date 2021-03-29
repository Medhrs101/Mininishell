/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:42:39 by moharras          #+#    #+#             */
/*   Updated: 2019/10/20 14:50:37 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			res;
	void			*p;

	res = count * size;
	if (!(p = malloc(res)))
		return (NULL);
	ft_bzero(p, res);
	return (p);
}
