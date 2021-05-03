/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:39:30 by moharras          #+#    #+#             */
/*   Updated: 2021/05/03 14:08:33 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_initial(void)
{
	t_var	*v;

	v = get_struct_var(NULL);
	v->erno = 0;
	v->flg_s_q = 0;
	v->flg_d_q = 0;
	v->flg_r_r = 0;
	v->flg_l_r = 0;
	v->flg_d_r = 0;
	v->flg_b_s = 0;
	v->flg_p = 0;
	v->flg_s_c = 0;
}

int	sum_all_flag(void)
{
	t_var	*v;
	int		sum;

	sum = 0;
	v = get_struct_var(NULL);
	sum = v->flg_d_r + v->flg_l_r + v->flg_r_r + v->flg_s_c + v->flg_p;
	return (sum);
}

int	sum_flag(void)
{
	t_var	*v;
	int		sum;

	sum = 0;
	v = get_struct_var(NULL);
	sum = v->flg_d_r + v->flg_r_r + v->flg_l_r;
	return (sum);
}

int	char_off(int c)
{
	if (c > 32 && c < 127)
		return (1);
	return (0);
}

void	off_flags(void)
{
	t_var	*v;

	v = get_struct_var(NULL);
	v->flg_d_r = 0;
	v->flg_r_r = 0;
	v->flg_l_r = 0;
	v->flg_p = 0;
	v->flg_s_c = 0;
}
