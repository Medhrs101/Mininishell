/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:44 by moharras          #+#    #+#             */
/*   Updated: 2021/05/04 16:18:14 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inverse(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] < 0)
			tab[i] *= -1;
		i++;
	}
}

int	is_empty(char *tb)
{
	int	i;

	i = 0;
	while (tb[i])
	{
		if (tb[i] != -3 && tb[i] != -2)
			return (0);
		i++;
	}
	return (1);
}

void	inverse_args(char **tb)
{
	int	i;
	int	j;

	i = -1;
	while (tb[++i])
	{
		j = -1;
		while (tb[i][++j])
		{
			if ((tb[i][j] == -3 || tb[i][j] == -2) && is_empty(tb[i]))
			{
				free(tb[i]);
				tb[i] = ft_strdup("");
				break ;
			}
			else if (tb[i][j] == -3 || tb[i][j] == -2)
			{
				override(tb[i], j);
				j--;
			}
			else if (tb[i][j] < 0)
				tb[i][j] *= -1;
		}
	}
}

char	*get_v_dolar(char *v_dolar)
{
	t_env	*tmp;
	t_var	*v;

	v = get_struct_var(NULL);
	tmp = v->m_gl->envar;
	while (tmp)
	{
		if (!ft_strcmp(v_dolar, tmp->ident))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	inverse_file(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[0] != -1 && tab[0] != -2 && tab[0] != -3 && tab[i] < 0)
			tab[i] *= -1;
		i++;
	}
}

char	*inverse_dolar(char *dolar)
{
	int	i;

	i = 0;
	while (dolar[i])
	{
		dolar[i] *= -1;
		i++;
	}
	return (dolar);
}
