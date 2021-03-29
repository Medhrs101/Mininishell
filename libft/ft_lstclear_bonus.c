/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:59:59 by moharras          #+#    #+#             */
/*   Updated: 2019/11/10 14:17:51 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list				*alst;
	t_list				*temp;

	alst = *lst;
	while (alst != NULL)
	{
		temp = alst;
		(*del)(alst->content);
		alst = (alst)->next;
		free(temp);
	}
	*lst = NULL;
}
