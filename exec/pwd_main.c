/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:32:02 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 15:35:06 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_main(void)
{
	char	path[PATH_MAX];

	getcwd(path, sizeof(path));
	ft_putendl_fd(path, 1);
	con.exit_stat = 0;
}

int	count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	check_path(t_global *m_gl, char **path)
{
	char	*tmp;

	tmp = *path;
	if (path[0][0] == '~' && path[0][1] != '~')
	{
		*path = ft_strjoin(m_gl->home, &path[0][1]);
		free(tmp);
	}
}
