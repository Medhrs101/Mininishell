/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:09:39 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/05 10:47:02 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **env_tab(t_global *m_gl)
{
	t_env *env_l;
	char **tab;
	char *tmp;
	int i;

	env_l = m_gl->envar;
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_lstsize_m(env_l) + 1));
	while (env_l)
	{
		if (env_l->equal == '=')
		{
			tab[i] = ft_strjoin(env_l->ident, "=");
			tmp = tab[i];
			tab[i] = ft_strjoin(tab[i], env_l->value);
			free(tmp);
		}
		i++;
		env_l = env_l->next;
	}
	tab[i] = NULL;
	return (tab);
}

char *check_pathh(char **path, char *cmd)
{
	char *str;
	char *tmp;
	int i;
	struct stat buffer;

	i = 0;
	if (stat(cmd, &buffer))
	{
		tmp = ft_strjoin("/", cmd);
		if (path)
			while (path[i])
			{
				str = ft_strjoin(path[i], tmp);
				if (!stat(str, &buffer))
				{
					free(tmp);
					free_tab(path);
					return (str);
				}
				else
					free(str);
				i++;
			}
	}
	else
		return (cmd);
	print_err("bash: %s: command not found\n", cmd);
	free(tmp);
	free_tab(path);
	return (NULL);
}

char *get_path(t_global *m_gl, char *cmd)
{
	t_env *env_l;
	char **tab;
	struct stat buffer;
	int i;

	i = 0;
	env_l = m_gl->envar;
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, "PATH"))
		{
			tab = ft_split(env_l->value, ':');
		}
		env_l = env_l->next;
	}
	return (check_pathh(tab, cmd));
}

void exec_main(t_global *m_gl, t_node *node)
{
	char *path;
	char **args;
	char **envp;

	args = node->args;
	path = get_path(m_gl, args[0]);
	envp = env_tab(m_gl);
	m_gl->pid = fork();
	if (m_gl->pid == 0)
		execve(path, args, envp);
	else
	{
		wait(&(m_gl->pid));
		if (WIFEXITED(m_gl->pid))
		{
			printf("Exit status: %d\n", WEXITSTATUS(m_gl->pid));
			m_gl->exit_stat = WEXITSTATUS(m_gl->pid);
		}
	}
}