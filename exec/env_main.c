/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:07:16 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/29 14:44:03 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_main(t_global *m_gl, char **tab)
{
	t_env *tmp;

	tmp = m_gl->envar;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->ident,1);
			ft_putchar_fd(tmp->equal, 1);
			ft_putendl_fd(tmp->value,1);
		}
		tmp = tmp->next;
	}
	con.exit_stat = 0;
}

void	change_value(char *ident, char *value)
{
	t_env	*tmp;
	t_var	*v;

	v = get_struct_var(NULL);
	tmp = v->m_gl->envar;
	while (tmp)
	{
		if (!ft_strcmp(ident, tmp->ident))
		{
			free(tmp->value);
			tmp->value = value;
		}
		tmp = tmp->next;
	}
}

void	env_copy(t_global *m_gl, char **env_t)
{
	t_env	*tmp;
	char	**tab;
	char	c;

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

void	modify_path(t_env *env_l)
{
	char	*tmp;
	char	path[PATH_MAX];
	char	*str;

	getcwd(path, PATH_MAX);
	str = ft_strjoin(":", path);
	tmp = env_l->value;
	env_l->value = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
}
