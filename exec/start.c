/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:22:30 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 13:03:00 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init(t_global *m_gl)
{
	m_gl->home = NULL;
	con.exit_stat = 0;
	m_gl->stdo = 1;
	m_gl->pid = 0;
	m_gl->stdi = 0;
}

long long ft_atoi_l(const char *str)
{
	int i;
	long long nb;
	int signe;

	i = 0;
	nb = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '\0')
		return (0);
	else if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	return (nb * (long long)signe);
}

int check_built(t_global *m_gl, t_node *node)
{
	char **cmd;
	t_env *env_l;

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

void execute(t_global *m_gl, t_node *node)
{
	t_node *tmp;

	tmp = node;
	if (node->args[0] && !check_built(m_gl, tmp))
	{
		exec_main(m_gl, tmp);
	}
}
