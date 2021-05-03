/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:14 by moharras          #+#    #+#             */
/*   Updated: 2021/05/03 13:57:21 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	v_dolar_not_null(t_var *v, int j, t_hp *t)
{
	t->tmp1 = ft_substr(v->sc_sp[j], 0, t->i);
	t->tmp2 = ft_strjoin(t->tmp1, t->v_dolar);
	t->tmp3 = ft_strjoin(t->tmp2, &v->sc_sp[j][t->i + 1 + t->end]);
	free(v->sc_sp[j]);
	v->sc_sp[j] = t->tmp3;
	t->i = t->i - 1 + ft_strlen(t->v_dolar);
	free(t->tmp2);
	free(t->tmp1);
	free(t->v_dolar);
	free(t->dolar);
	if (t->r == 1)
		t->r = 0;
}

void	v_dolar_null(t_var *v, int j, t_hp *t)
{
	if (!dolar_null_in_start(v, j, t))
		return ;
	else if (t->r == 1 && is_red(v->sc_sp[j][t->i + ft_strlen(t->dolar) + 1]))
	{
		free(t->dolar);
		t->r = 0;
		v->sc_sp[j][t->i] -= 37;
		return ;
	}
	if (t->d == 1 && v->sc_sp[j][t->i + ft_strlen(t->dolar) + 1] == '"')
	{
		v->sc_sp[j][t->i + ft_strlen(t->dolar) + 1] -= 36;
		t->d = 0;
	}
	t->tmp1 = ft_substr(v->sc_sp[j], 0, t->i);
	t->tmp2 = ft_strjoin(t->tmp1, &v->sc_sp[j][t->i + ft_strlen(t->dolar) + 1]);
	free(v->sc_sp[j]);
	v->sc_sp[j] = t->tmp2;
	t->i -= 1;
	free(t->dolar);
	free(t->tmp1);
}

void	dolar_hundle(int j, t_hp *t)
{
	t_var	*v;

	t->end = 0;
	v = get_struct_var(NULL);
	t->end = end_dolar(v->sc_sp[j], t->i + 1);
	t->dolar = ft_substr(v->sc_sp[j], t->i + 1, t->end);
	if (v->sc_sp[j][t->i + 1] == '?')
		t->v_dolar = ft_itoa(con.exit_stat);
	else
		t->v_dolar = get_v_dolar(t->dolar);
	if (t->v_dolar != NULL)
	{
		inverse_dolar(t->v_dolar);
		v_dolar_not_null(v, j, t);
	}
	else
		v_dolar_null(v, j, t);
}
