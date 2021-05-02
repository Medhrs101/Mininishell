/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 11:28:12 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 14:24:41 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_p(t_node *node)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = node;
	while (tmp)
	{
		i++;
		tmp = tmp->link;
	}
	return (i - 1);
}

void	pip_or_not(t_var *var)
{
	if (!var->node->link)
	{
		if (out_red(var, var->node) && var->node->cmd)
			execute(var->m_gl, var->node);
	}
	else
		piping(var);
}

t_pip	*pipe_struct(t_var *var)
{
	t_pip	*t_p;

	t_p = (t_pip *)malloc(sizeof(t_pip));
	t_p->numofpipe = count_p(var->node);
	t_p->pipefd = (int *)malloc((2 * t_p->numofpipe) * sizeof(int));
	t_p->pid = (int *)malloc((t_p->numofpipe + 1) * sizeof(int));
	return (t_p);
}

void	duping(t_var *var, t_pip *t_p, int *j)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = var->node;
	while (tmp)
	{
		t_p->pid[*j / 2] = fork();
		if (t_p->pid[*j / 2] == 0)
		{
			if (tmp->link)
				dup2(t_p->pipefd[*j + 1], 1);
			if (*j != 0)
				dup2(t_p->pipefd[*j - 2], 0);
			i = -1;
			while (++i < 2 * t_p->numofpipe)
				close(t_p->pipefd[i]);
			if (out_red(var, tmp))
				execute(var->m_gl, tmp);
			exit(con.exit_stat);
		}
		tmp = tmp->link;
		*j += 2;
	}
}

void	piping(t_var *var)
{
	int		status;
	int		i;
	int		j;
	t_pip	*t_p;

	t_p = pipe_struct(var);
	i = 0;
	j = 0;
	while (i < t_p->numofpipe)
	{
		pipe(t_p->pipefd + i * 2);
		i++;
	}
	duping(var, t_p, &j);
	i = -1;
	while (++i < 2 * t_p->numofpipe)
		close(t_p->pipefd[i]);
	i = -1;
	while (++i < t_p->numofpipe + 1)
	{
		waitpid(t_p->pid[i], &status, 0);
		con.exit_stat = WEXITSTATUS(status);
	}
}
