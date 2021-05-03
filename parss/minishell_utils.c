/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:25 by moharras          #+#    #+#             */
/*   Updated: 2021/05/03 14:24:56 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int erno)
{
	t_var	*v;

	v = get_struct_var(NULL);
	v->erno = erno;
	con.exit_stat = 258;
	ft_putstr_fd("minishell: ", 2);
	if (v->erno == NEWLINE)
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	else if (v->erno == UN_PIPE)
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	else if (v->erno == UN_LR)
		ft_putendl_fd("syntax error near unexpected token `<'", 2);
	else if (v->erno == UN_RR)
		ft_putendl_fd("syntax error near unexpected token `>'", 2);
	else if (v->erno == UN_DR)
		ft_putendl_fd("syntax error near unexpected token `>>'", 2);
	else if (v->erno == UN_SC)
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
	else if (v->erno == UN_DSC)
		ft_putendl_fd("syntax error near unexpected token `;;'", 2);
	else if (v->erno == UN_DPIPE)
		ft_putendl_fd("syntax error near unexpected token `||'", 2);
	return (v->erno);
}

void	hundle_end(void)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (sum_flag() || v->flg_s_q || v->flg_d_q || v->flg_b_s || v->flg_p)
	{
		print_error(NEWLINE);
		free(v->input);
		return ;
	}
	else if (!sum_all_flag(v))
		divid_input();
}

void	double_quote(int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (v->flg_d_q)
		v->flg_d_q = 0;
	else if (v->flg_s_q)
		v->input[i] *= -1;
	else if (!v->flg_d_q && !v->flg_s_q)
	{
		if (sum_all_flag())
			off_flags();
		v->flg_d_q = 1;
	}
}

void	simple_quote(int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (v->flg_s_q)
		v->flg_s_q = 0;
	else if (v->flg_d_q)
		v->input[i] *= -1;
	else if (!v->flg_d_q && !v->flg_s_q)
	{
		if (sum_all_flag())
			off_flags();
		v->flg_s_q = 1;
	}
}
