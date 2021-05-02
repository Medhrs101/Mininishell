/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:18 by moharras          #+#    #+#             */
/*   Updated: 2021/05/02 14:39:19 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bs_hundle(char *tb, t_hp *t)
{
	if (tb[t->i + 1] == '\\')
	{
		tb[t->i] = -92;
		override(tb, t->i + 1);
	}
	else
	{
		if (tb[t->i + 1] == '$')
			t->bs_erno = 1;
		if (tb[t->i + 1] != '$' && tb[t->i + 1] > 0 && !t->d)
			tb[t->i + 1] *= -1;
		override(tb, t->i);
		t->i -= 1;
	}
}

int	bs_work(char *tb, t_hp *t)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (!t->d && !t->s)
	{
		if (t->r == 1)
			t->r = 0;
		return (1);
	}
	else if (t->d && (tb[t->i + 1] == '\\' || tb[t->i + 1] == -34
			|| tb[t->i + 1] == '$' || tb[t->i + 1] == '`'))
	{
		if (t->r == 1)
			t->r = 0;
		return (1);
	}
	return (0);
}

void	off_r(int *r)
{
	if (*r ==1)
		*r = 0;
}

int	hundle_input(int j, t_var *v)
{
	t_hp	*t;

	t = (t_hp *)malloc(sizeof(t_hp));
	hp_initial(t);
	while (v->sc_sp[j][++t->i])
	{
		if (v->sc_sp[j][t->i] == '\'' || v->sc_sp[j][t->i] == '"')
			hundle_s_d(v, j, t);
		else if (!t->s && !t->d
			&& is_redirection(v->sc_sp[j][t->i], v->sc_sp[j][t->i + 1], t))
		{
			if (v->sc_sp[j][t->i + 1] == '>')
				t->i++;
			else
				continue ;
		}
		else if (v->sc_sp[j][t->i] == '\\' && bs_work(v->sc_sp[j], t))
			bs_hundle(v->sc_sp[j], t);
		else if (v->sc_sp[j][t->i] == '$' && dolar_work(v->sc_sp[j], t))
			dolar_hundle(j, t);
		else if (char_off(v->sc_sp[j][t->i]))
			off_r(&t->r);
	}
	free(t);
	return (1);
}
