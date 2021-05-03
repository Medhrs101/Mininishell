/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:09:39 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/03 14:49:26 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_tab(t_global *m_gl)
{
	t_env	*env_l;
	char	**tab;
	char	*tmp;
	int		i;

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
			i++;
		}
		env_l = env_l->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*get_path(t_global *m_gl, char *cmd)
{
	t_env		*env_l;
	char		**tab;
	int			i;

	i = 0;
	tab = NULL;
	env_l = m_gl->envar;
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, "PATH"))
			tab = ft_split(env_l->value, ':');
		env_l = env_l->next;
	}
	return (check_pathh(tab, cmd));
}

void	exec_main(t_global *m_gl, t_node *node)
{
	char	*path;
	char	**args;
	char	**envp;
	int		pid;

	args = node->args;
	con.exit_stat = 0;
	path = get_path(m_gl, args[0]);
	envp = env_tab(m_gl);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(path, args, envp);
			exit(0);
		}
		else
			wait_child(pid);
	}
	free_tab(envp);
	free(path);
}

void	wait_child(int pid)
{
	int	statu;

	waitpid(pid, &(statu), 0);
	if (WEXITSTATUS(statu))
		con.exit_stat = WEXITSTATUS(statu);
}
