/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:26:49 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/29 14:12:57 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	head = NULL;
	if (lst)
	{
		head = ft_lstnew((*f)(lst->content));
		if (!head)
			return (NULL);
		tmp = head;
		lst = lst->next;
		while (lst)
		{
			tmp->next = ft_lstnew((*f)(lst->content));
			if (!tmp->next)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			tmp = tmp->next;
			lst = lst->next;
		}
	}
	return (head);
}
