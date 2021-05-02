/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:37:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 14:30:07 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	out_redirect(t_var *var, t_file *tmp)
{
	if (tmp->type == '>')
	{
		var->out_fd = open(tmp->name_file,
				O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (var->out_fd < 0)
		{
			print_err("Minishell: %s: ", tmp->name_file, 0);
			print_err("%s\n", strerror(errno), 1);
			return (0);
		}
		dup2(var->out_fd, STDOUT);
		close(var->out_fd);
	}
	return (1);
}

int	in_redirect(t_var *var, t_file *tmp)
{
	if (tmp->type == '<')
	{
		var->in_fd = open(tmp->name_file, O_RDONLY);
		if (var->in_fd < 0)
		{
			print_err("Minishell: %s: ", tmp->name_file, 0);
			print_err("%s\n", strerror(errno), 1);
			return (0);
		}
		dup2(var->in_fd, STDIN);
		close(var->in_fd);
	}
	return (1);
}

int	app_redirect(t_var *var, t_file *tmp)
{
	if (tmp->type == 'a')
	{
		var->app_fd = open(tmp->name_file,
				O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (var->app_fd < 0)
		{
			print_err("Minishell: %s: ", tmp->name_file, 0);
			print_err("%s\n", strerror(errno), 1);
			return (0);
		}
		dup2(var->app_fd, STDOUT);
		close(var->app_fd);
	}
	return (1);
}

int	out_red(t_var *var, t_node *node)
{
	t_file	*tmp;

	tmp = node->file;
	while (tmp)
	{
		if (tmp->name_file[0] == -1)
		{
			print_err("Minishell: $%s: ambiguous redirect\n",
				tmp->name_file + 1, 1);
			return (0);
		}
		if (tmp->name_file[0] == -2)
		{
			free(tmp->name_file);
			tmp->name_file = ft_strdup("");
		}
		if (!out_redirect(var, tmp)
			|| !in_redirect(var, tmp) || !app_redirect(var, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
