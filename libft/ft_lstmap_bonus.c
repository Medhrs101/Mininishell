/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:55:59 by moharras          #+#    #+#             */
/*   Updated: 2019/11/10 14:23:10 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_lst;
	t_list		*lst_rt;

	lst_rt = NULL;
	if (lst)
	{
		while (lst != NULL)
		{
			if (!(new_lst = ft_lstnew(((*f)(lst->content)))))
			{
				ft_lstclear(&lst_rt, del);
				return (NULL);
			}
			ft_lstadd_back(&lst_rt, new_lst);
			lst = lst->next;
		}
	}
	return (lst_rt);
}
