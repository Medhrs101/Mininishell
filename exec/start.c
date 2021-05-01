/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:22:30 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/01 12:22:59 by ymarji           ###   ########.fr       */
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

void	exit_stat(int stat, t_env *env_l, char **cmd)
{
	while (env_l)
	{
		free(env_l->ident);
		free(env_l->value);
		free(env_l);
		env_l = env_l->next;
	}
	clear_lst_cmd_args();
	if (cmd[1])
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
		exit_stat(con.exit_stat, m_gl->envar, cmd);
	else
		return (0);
	return (1);
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
