#include "../minishell.h"

int	behind_s_c(int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (v->input[0] == ';' && v->input[1] != ';' && print_error(UN_SC))
		return (0);
	else if ((v->flg_s_q || v->flg_d_q))
	{
		v->input[i] *= -1;
		return (0);
	}
	else if (v->input[i + 1] == ';' && print_error(UN_DSC))
		return (0);
	else if (v->flg_s_c && print_error(UN_SC))
		return (0);
	else
	{
		while (v->input[++i])
			if (char_off(v->input[i]))
				return (1);
	}
	return (0);
}

void	semi_colone(void)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (!v->flg_d_q && !v->flg_s_q)
		v->flg_s_c = 1;
}

int	pip(int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (v->input[0] == '|' && v->input[1] != '|' )
		return (print_error(UN_PIPE));
	if (!v->flg_s_q && !v->flg_d_q && v->input[i + 1] == '|')
		return (print_error(UN_DPIPE));
	else if (sum_flag() || v->flg_s_c)
		return (print_error(UN_PIPE));
	else if (v->flg_s_q || v->flg_d_q)
		v->input[i] *= -1;
	else if (!v->flg_d_q && !v->flg_s_q)
		v->flg_p = 1;
	return (0);
}

void	b_slash(int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (v->flg_s_q)
	{
		v->input[i] *= -1;
		return ;
	}
	if (v->flg_b_s)
		 v->flg_b_s = 0;
	else
		v->flg_b_s = 1;
	if (v->flg_b_s && v->input[i + 1] == '"')
	{
		if (sum_all_flag())
			off_flags();
		v->input[i + 1] *= -1;
	}
	if (v->flg_b_s && !v->flg_d_q
		&& (v->input[i + 1] == '\'' || v->input[i + 1] == ';'))
		v->input[i + 1] *= -1;
}
