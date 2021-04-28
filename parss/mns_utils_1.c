#include "../minishell.h"

void    ft_initial()
{
    t_var *v;

    v = get_struct_var(NULL);
    v->erno = 0;
    v->flg_s_q = 0;
    v->flg_d_q = 0;
    v->flg_r_r = 0;
    v->flg_l_r = 0;
    v->flg_d_r = 0;
    v->flg_b_s = 0;
    v->flg_p = 0;
}

int sum_all_flag()
{
    int sum;
    t_var *v;

    sum = 0;
    v = get_struct_var(NULL);
    sum = v->flg_d_r + v->flg_l_r + v->flg_r_r + v->flg_s_c + v->flg_p;
    return (sum);
}

int sum_flag()
{
    int sum;
    t_var *v;
    sum = 0;

    v = get_struct_var(NULL);
    sum = v->flg_d_r + v->flg_r_r + v->flg_l_r;
    return (sum);
}

int		char_off(int c)
{
	if (c > 32 && c < 127)
		return (1);
	return (0);
}

void    off_flags()
{
    t_var *v;

    v = get_struct_var(NULL);
    v->flg_d_r = 0;
    v->flg_r_r = 0;
    v->flg_l_r = 0;
    v->flg_p = 0;
    v->flg_s_c = 0;
}