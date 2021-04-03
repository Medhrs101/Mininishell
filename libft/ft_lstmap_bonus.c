/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:26:49 by ymarji            #+#    #+#             */
/*   Updated: 2019/11/06 10:56:52 by ymarji           ###   ########.fr       */
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
		if (!(head = ft_lstnew((*f)(lst->content))))
			return (NULL);
		tmp = head;
		lst = lst->next;
		while (lst)
		{
			if (!(tmp->next = ft_lstnew((*f)(lst->content))))
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
