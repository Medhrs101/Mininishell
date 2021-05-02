/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:35:44 by moharras          #+#    #+#             */
/*   Updated: 2021/05/02 14:47:28 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	end_dolar(char *tb, int i)
{
	int	cpt;

	cpt = 0;
	if (tb[i] == '?' || isdigit(tb[i]))
		return (1);
	while (tb[i])
	{
		if (tb[i] < 0 || ft_strrchr("=~\\/%#{}$*+-.|:?@[]^ \"'", tb[i]))
			break ;
		cpt++;
		i++;
	}
	return (cpt);
}

int	dolar_work(char *tb, t_hp *t)
{
	if (t->bs_erno)
	{
		t->bs_erno = 0;
		return (0);
	}
	if (t->d && tb[t->i + 1] == '"')
		return (0);
	if (tb[t->i - 1] == '\\' || t->s || !tb[t->i + 1] || tb[t->i + 1] == '$')
		return (0);
	return (1);
}

int	dolar_null_in_start(t_var *v, int j, t_hp *t)
{
	if (t->i == 0 && !v->sc_sp[j][t->i + ft_strlen(t->dolar) + 1])
	{
		free(t->dolar);
		v->tmp1 = ft_strdup("");
		free(v->sc_sp[j]);
		v->sc_sp[j] = v->tmp1;
		return (0);
	}
	return (1);
}
