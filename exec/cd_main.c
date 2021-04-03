/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:10:26 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/03 14:30:28 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ls(void)
{
	struct dirent *de; // Pointer for directory entry

	// opendir() returns a pointer of DIR type.
	DIR *dr = opendir(".");

	if (dr == NULL) // opendir returns NULL if couldn't open directory
	{
		printf("Could not open current directory");
		return 0;
	}

	while ((de = readdir(dr)) != NULL)
	{
		if (de->d_name[0] != '.')
			printf("%s\n", de->d_name);
	}

	closedir(dr);
	return 0;
}

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
		printf("bash: cd: HOME not set\n");
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
			env_l->value = ft_strdup(path);
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
			printf("bash: cd: OLDPWD not set\n");
		else if (!opendir(path) && c != 2)
			printf("cd: no such file or directory: %s\n", path);
		else
		{
			chdir(path);
			set_env_pwd(m_gl);
		}
	}
}