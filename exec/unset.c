/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:09 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/03 13:11:38 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ident_val(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	unset(t_global *m_gl, char **tab)
{
	t_env	*env_l;
	int		i;

	i = -1;
	env_l = m_gl->envar;
	while (tab[++i])
	{
		if (!ident_val(tab[i]))
			print_err("Minishell: unset: `%s': not a valid identifier\n",
				tab[i], 1);
		env_l = m_gl->envar;
		while (env_l)
		{
			if (!ft_strcmp(env_l->ident, tab[i]))
			{
				ft_deletenode(&(m_gl->envar), env_l);
				break ;
			}
			env_l = env_l->next;
		}
	}
	return (0);
}

void	print_err(char *str, char *arg, int errnb)
{
	int	fd;

	con.exit_stat = errnb;
	fd = dup(1);
	dup2(2, 1);
	if (arg)
		printf(str, arg);
	else
		printf("%s\n", str);
	dup2(fd, 1);
	close(fd);
}
