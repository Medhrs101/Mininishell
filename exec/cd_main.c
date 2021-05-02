/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:10:26 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/30 16:15:49 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_path(t_global *m_gl, char **path)
{
	char *tmp;

	tmp = *path;
	if (path[0][0] == '~' && path[0][1] != '~')
	{
		*path = ft_strjoin(m_gl->home, &path[0][1]);
		free(tmp);
	}
}

char *ret_path(t_global *m_gl, char *line)
{
	t_env *env_l;
	char *path;
	char *home;

	env_l = m_gl->envar;
	home = NULL;
	path = NULL;
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, "HOME"))
			home = env_l->value;
		env_l = env_l->next;
	}
	if (!line && !home)
		printf("Minishell: cd: HOME not set\n");
	else if (!line)
		path = ft_strdup(home);
	else if (line[0] == '~' && !home)
		path = ft_strjoin(m_gl->home, &line[1]);
	else if (line[0] == '~')
		path = ft_strjoin(home, &line[1]);
	else
		path = ft_strdup(line);
	return (path);
}

void set_env_oldpwd(t_global *m_gl, char *path)
{
	t_env *env_l;
	char *tmp;
	int i;

	i = -1;
	env_l = m_gl->envar;
	while (env_l)
	{
		if (!(i = ft_strcmp(env_l->ident, "OLDPWD")))
		{
			tmp = env_l->value;
			env_l->value = ft_strdup(path);
			free(tmp);
			break;
		}
		env_l = env_l->next;
	}
	if (i != 0)
	{
		env_l = ft_lstnew_m(ft_strdup("OLDPWD"), path, '=');
		ft_lstadd_back_m(&(m_gl->envar), env_l);
	}
}

void set_env_pwd(t_global *m_gl)
{
	t_env *env_l;
	char path[PATH_MAX];
	char *tmp;

	env_l = m_gl->envar;
	tmp = NULL;
	getcwd(path, sizeof(path));
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, "PWD"))
		{
			tmp = env_l->value;
			env_l->equal = '=';
			env_l->value = ft_strdup(path);
			free(tmp);
			break;
		}
		env_l = env_l->next;
	}
	set_env_oldpwd(m_gl, tmp);
}

int oldpath(t_global *m_gl, char **path)
{
	t_env *env_l;
	int c;

	c = 0;
	env_l = m_gl->envar;
	if (!ft_strcmp(*path, "-"))
	{
		c = 1;
		while (env_l)
		{
			if (!ft_strcmp(env_l->ident, "OLDPWD"))
			{
				c = 2;
				free(*path);
				*path = ft_strdup(env_l->value);
				env_l->equal = '=';
			}
			env_l = env_l->next;
		}
		if (c == 2)
			printf("%s\n", *path);
	}
	return (c);
}

void cd_main(t_global *m_gl, char **tab)
{
	char *path;
	int c;

	path = ret_path(m_gl, tab[1]);
	if (path)
		check_path(m_gl, &path);
	if (path)
	{
		if ((c = oldpath(m_gl, &path)) == 1)
			ft_putendl_fd("Minishell: cd: OLDPWD not set", 2);
		else if (!opendir(path) && c != 2)
			print_err("cd: %s: no such file or directory: \n", path, 1);
		else
		{
			chdir(path);
			set_env_pwd(m_gl);
			con.exit_stat = 0;
		}
	}
	free(path);
}