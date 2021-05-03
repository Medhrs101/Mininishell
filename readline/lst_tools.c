/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:24:11 by moharras          #+#    #+#             */
/*   Updated: 2021/05/03 14:31:25 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_hst	*get_new_node(void)
{
	t_hst	*new_node;

	new_node = (t_hst *)malloc(sizeof(t_hst));
	new_node->next = NULL;
	new_node->curpos = 0;
	new_node->curr_buff = (char *)malloc(sizeof(char) * 2);
	new_node->old_buff = (char *)malloc(sizeof(char) * 2);
	ft_bzero(new_node->curr_buff, sizeof(char) * 2);
	ft_bzero(new_node->old_buff, sizeof(char) * 2);
	new_node->prev = NULL;
	return (new_node);
}

void	insert_at_tail(t_rdl *rdl, t_hst *new_node)
{
	t_hst	*tmp;

	tmp = rdl->head;
	if (rdl->head == NULL)
	{
		rdl->head = new_node;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_node;
	new_node->prev = tmp;
}
