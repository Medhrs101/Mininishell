/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:07:09 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/01 10:17:13 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ident_val(char *str)
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

int unset(t_global *m_gl, char **tab)
{
	t_env *env_l;

	env_l = m_gl->envar;
	if (!ident_val(tab[1]))
	{
		printf("bash: unset: `%s': not a valid identifier\n", tab[1]);
		m_gl->exit_stat = 1;
	}
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, tab[1]))
			ft_deletenode(&(m_gl->envar), env_l);
		env_l = env_l->next;
	}
	return (0);
}

void print_err(char *str, char *arg)
{
	dup2(2, 1);
	printf(str, arg);
	dup2(1, 2);
}