/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_sd_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:21 by moharras          #+#    #+#             */
/*   Updated: 2021/05/02 14:39:22 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hundle_dq(t_var *v, int j, t_hp *t)
{
	if (t->d)
		t->d = 0;
	else
		t->d = 1;
	if (t->d && v->sc_sp[j][t->i + 1] == '"')
	{
		v->sc_sp[j][t->i + 1] -= 36;
		t->d = 0;
		t->r = 0;
	}
}

void	hundle_sq(t_var *v, int j, t_hp *t)
{
	if (t->s)
		t->s = 0;
	else
		t->s = 1;
	if (t->s && v->sc_sp[j][t->i + 1] == '\'')
	{
		v->sc_sp[j][t->i + 1] = -2;
		t->s = 0;
		t->r = 0;
	}
}

void	hundle_s_d(t_var *v, int j, t_hp *t)
{
	if (v->sc_sp[j][t->i] == '"')
		hundle_dq(v, j, t);
	else if (v->sc_sp[j][t->i] == '\'')
		hundle_sq(v, j, t);
	override(v->sc_sp[j], t->i);
	t->i -= 1;
}
