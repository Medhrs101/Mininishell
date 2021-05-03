/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:23:23 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/03 15:15:04 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_path(char **path, char *cmd)
{
	char		*tmp;
	char		*str;
	struct stat	buffer;
	int			i;

	i = -1;
	tmp = ft_strjoin("/", cmd);
	if (path)
	{
		while (path[++i])
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
		}
	}
	free(tmp);
	return (NULL);
}

char	*relative_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		print_err("Minishell: %s: is a directory\n", cmd, 1);
		free(dir->__dd_buf);
		free(dir);
		return (NULL);
	}
	else
		return (ft_strdup(cmd));
}

char	*check_pathh(char **path, char *cmd)
{
	char		*str;
	int			i;
	struct stat	buffer;

	i = 0;
	if (stat(cmd, &buffer))
	{
		str = join_path(path, cmd);
		if (str)
			return (str);
	}
	else
	{
		free_tab(path);
		return (relative_path(cmd));
	}
	if (ft_strchr(cmd, '/'))
		print_err("Minishell: %s: No such file or directory\n", cmd, 127);
	else
		print_err("Minishell: %s: command not found\n", cmd, 127);
	free_tab(path);
	return (NULL);
}
