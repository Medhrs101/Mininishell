/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:40 by moharras          #+#    #+#             */
/*   Updated: 2021/05/02 14:39:41 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(int c, int d, t_hp *t)
{
	if (c == '>' || c == '<' || (c == '>' && d == '>'))
	{
		t->r = 1;
		return (1);
	}
	return (0);
}

void	inverse_input(int i)
{
	t_var	*v;
	int		j;

	v = get_struct_var(NULL);
	j = 0;
	while (v->sc_sp[i][j])
	{
		if (v->sc_sp[i][j] < 0)
			v->sc_sp[i][j] *= -1;
		j++;
	}
}

void	override(char *tb, int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	while (tb[i])
	{
		tb[i] = tb[i + 1];
		i++;
	}
}

int	isdigit(int c)
{
	if (c <= 57 && c > 48)
		return (1);
	else
		return (0);
}

int	ft_argchr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
