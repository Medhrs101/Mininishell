/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parss_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:50 by moharras          #+#    #+#             */
/*   Updated: 2021/05/04 16:18:51 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_cmd_list(t_node *node)
{
	t_node	*current;
	t_var	*var;

	var = get_struct_var(NULL);
	current = var->node;
	if (current == NULL)
		var->node = node;
	else
	{
		while (current->link)
			current = current->link;
		current->link = node;
	}
}

t_node	*create_node(t_node *node)
{
	node = (t_node *)malloc(sizeof(t_node));
	node->file = NULL;
	node->link = NULL;
	node->cmd = NULL;
	return (node);
}

void	clear_lst_files(t_node *node)
{
	t_file	*current;
	t_file	*tmp;

	current = node->file;
	if (current == NULL)
		return ;
	else
	{
		while (current)
		{
			free(current->name_file);
			tmp = current;
			current = current->next;
			free(tmp);
		}
	}
}

void	clear_lst_cmd_args(void)
{
	t_node	*current;
	t_var	*var;
	t_node	*tmp;

	var = get_struct_var(NULL);
	current = var->node;
	if (current == NULL)
		return ;
	else
	{
		while (current)
		{
			tmp = current;
			if (current->cmd)
				free_tab(current->args);
			clear_lst_files(current);
			current = current->link;
			free(tmp);
		}
	}
}
