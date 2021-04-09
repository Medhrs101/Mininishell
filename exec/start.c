/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:22:30 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/08 10:50:32 by ymarji           ###   ########.fr       */
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
		exit(0);
	else
		return (0);
	return (1);
}

void execute(t_global *m_gl, t_node *node)
{
	t_node *tmp;
	char **tab;
	int i;

	tmp = node;
	if (tab[0] && !(i = check_built(m_gl, tmp)))
		exec_main(m_gl, tmp);
		tmp = tmp->link;
	// free_tab(tab);
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