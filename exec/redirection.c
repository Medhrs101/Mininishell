/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:37:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/19 12:10:08 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	 out_red(t_var	*var, t_node *node)
{
	t_file 		*tmp;
	int fd;

	fd = 0;
	tmp = node->file;
	while (tmp)
	{
		if (tmp->type == '>')
		{
			if ((var->out_fd = open(tmp->name_file , O_CREAT | O_WRONLY | O_TRUNC, 0664)) < 0)
			{
				print_err("bash: %s: ", tmp->name_file, 0);
				print_err("%s\n", strerror(errno), 1);
				return (0);
			}
			dup2(var->out_fd, STDOUT);
			close(var->out_fd);
		}
		if (tmp->type == '<')
		{
			if ((var->in_fd = open(tmp->name_file , O_RDONLY)) < 0)
			{
				print_err("bash: %s: ", tmp->name_file, 0);
				print_err("%s\n", strerror(errno), 1);
				return (0);
			}
			dup2(var->in_fd, STDIN);
			close(var->in_fd);
		}
		if (tmp->type == 'a')
		{
			if ((var->app_fd = open(tmp->name_file , O_CREAT | O_WRONLY | O_APPEND, 0664)) < 0)
			{
				print_err("bash: %s: ", tmp->name_file, 0);
				print_err("%s\n", strerror(errno), 1);
				return (0);
			}
			dup2(var->app_fd, STDOUT);
			close(var->app_fd);
		}
		tmp = tmp->next;
	}
	return (1);
}