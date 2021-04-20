/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:22:30 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/19 14:24:05 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init(t_global *m_gl)
{
	m_gl->home = NULL;
	m_gl->exit_stat = 0;
	m_gl->stdo = 1;
	m_gl->pid = 0;
	m_gl->stdi = 0;
}

int check_built(t_global *m_gl, t_node *node)
{
	char	**cmd = node->args;
	t_env	*env_l;

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
	{
		while(env_l)
		{
			free(env_l->ident);
			free(env_l->value);
			free(env_l);
			env_l = env_l->next;
		}
		exit(0);
	}
	else
		return (0);
	return (1);
}

int		count_p(t_node *node)
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
	return i - 1;
}

void	pip_or_not(t_var *var)
{
	if (!var->node->link)
	{
		if (out_red(var, var->node))
			execute(var->m_gl,	var->node);
	}
	else
		piping(var);
}

void	piping(t_var *var)
{
	int numofpipe = count_p(var->node);
	int status;
	int	i;
	int j;
	t_node *tmp;
	pid_t pid;
	int		pipefd[2 * numofpipe];

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
	printf("Exit status: %d\n", con.exit_stat);
}

void 	execute(t_global *m_gl, t_node *node)
{
	t_node *tmp;
	int i;

	tmp = node;
	if (node->args[0] && !(i = check_built(m_gl, tmp)))
	{
		exec_main(m_gl, tmp);
	}
}

void modify_path(t_env *env_l)
{
	char *tmp;
	char path[PATH_MAX];
	char *str;

	getcwd(path, PATH_MAX);
	str = ft_strjoin(":", path);
	tmp = env_l->value;
	env_l->value = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
}

void env_copy(t_global *m_gl, char **env_t)
{
	t_env *tmp;
	char **tab;
	char c;

	m_gl->envar = NULL;
	while (*env_t)
	{
		c = 0;
		tab = ft_split(*env_t++, '=');
		if (tab[1])
			c = '=';
		tmp = ft_lstnew_m(ft_strdup(tab[0]), ft_strdup(tab[1]), c);
		if (!ft_strcmp(tmp->ident, "HOME"))
			m_gl->home = ft_strdup(tmp->value);
		if (!ft_strcmp(tmp->ident, "PATH"))
			modify_path(tmp);
		ft_lstadd_back_m(&(m_gl->envar), tmp);
		free_tab(tab);
	}
}

void	change_value(char *ident, char *value)
{
    t_env *tmp;
    t_var *v= get_struct_var(NULL);

    tmp = v->m_gl->envar;
    while(tmp)
    {
        if (!ft_strcmp(ident, tmp->ident))
		{
			free(tmp->value);
			tmp->value = value;
		}
        tmp = tmp->next;
    }
}