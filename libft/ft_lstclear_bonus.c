/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:25:53 by ymarji            #+#    #+#             */
/*   Updated: 2019/11/07 09:51:35 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*alst;
	t_list	*tmp;

	alst = *lst;
	tmp = alst;
	while (alst != NULL)
	{
		(*del)(alst->content);
		tmp = alst->next;
		free(alst);
		alst = tmp;
	}
	*lst = NULL;
}
