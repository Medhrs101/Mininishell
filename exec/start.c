/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:22:30 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/29 14:52:27 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init(t_global *m_gl)
{
	m_gl->home = NULL;
	m_gl->exit_stat = 0;
	m_gl->stdo = 1;
	m_gl->pid = 0;
	m_gl->stdi = 0;
}

void	exit_stat(int stat, t_env *env_l)
{
	while (env_l)
	{
		free(env_l->ident);
		free(env_l->value);
		free(env_l);
		env_l = env_l->next;
	}
	clear_lst_cmd_args();
	exit(stat);
}

int	check_built(t_global *m_gl, t_node *node)
{
	char	**cmd;
	t_env	*env_l;

	cmd = node->args;
	env_l = m_gl->envar;
	if (node->cmd && !ft_strcmp(node->cmd, "echo"))
		echo_main(m_gl, node->args);
	else if (node->cmd && !ft_strcmp(node->cmd, "cd"))
		cd_main(m_gl, cmd);
	else if (node->cmd && !ft_strcmp(node->cmd, "pwd"))
		pwd_main(m_gl, cmd);
	else if (node->cmd && !ft_strcmp(node->cmd, "env"))
		env_main(m_gl, cmd);
	else if (node->cmd && !ft_strcmp(node->cmd, "export"))
		export_main(m_gl, cmd);
	else if (node->cmd && !ft_strcmp(node->cmd, "unset"))
		unset(m_gl, cmd);
	else if (node->cmd && !ft_strcmp(node->cmd, "exit"))
		exit_stat(con.exit_stat, m_gl->envar);
	else
		return (0);
	return (1);
}

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

void	piping(t_var *var)
{
	int		numofpipe;
	int		status;
	int		i;
	int		j;
	t_node	*tmp;
	pid_t	pid;
	int		*pipefd;

	pipefd = (int *)malloc((2 * numofpipe) * sizeof(int));
	numofpipe = count_p(var->node);
	i = 0;
	j = 0;
	tmp = var->node;
	while (i < numofpipe)
	{
		pipe(pipefd + i * 2);
		i++;
	}
	while (tmp)
	{
		pid = fork();
		if (pid == 0)
		{
			if (tmp->link)
				dup2(pipefd[j + 1], 1);

			if (j != 0)
				dup2(pipefd[j - 2], 0);

			i = -1;
			while (++i < 2 * numofpipe)
				close(pipefd[i]);

			if (out_red(var, tmp))
				execute(var->m_gl, tmp);
			exit(con.exit_stat);
		}
		tmp	= tmp->link;
		j += 2;
	}
	i = -1;
	while (++i < 2 * numofpipe)
		close(pipefd[i]);
	i = -1;
	while (++i < numofpipe + 1)
	{
		wait(&status);
		con.exit_stat = WEXITSTATUS(status);
	}
}

void 	execute(t_global *m_gl, t_node *node)
{
	t_node	*tmp;

	tmp = node;
	if (node->args[0] && !check_built(m_gl, tmp))
	{
		exec_main(m_gl, tmp);
	}
}
