/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:06:10 by moharras          #+#    #+#             */
/*   Updated: 2019/11/10 16:09:16 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		if (new)
		{
			while (lst->next != NULL)
				lst = lst->next;
		}
		lst->next = new;
		new->next = NULL;
	}
}
