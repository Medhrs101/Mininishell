#include "../minishell.h"

int right_red(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!v->flg_s_q && !v->flg_d_q && sum_flag())
    {
        return (print_error(UN_RR));
    }
    else if (v->flg_s_q || v->flg_d_q)
        v->input[i] *= -1;
    else if (!v->flg_d_q && !v->flg_s_q)
        v->flg_r_r = 1;
    return (0);
}

int left_red(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!v->flg_s_q && !v->flg_d_q && sum_flag())
        return (print_error(UN_LR));
    else if (v->flg_s_q || v->flg_d_q)
        v->input[i] *= -1;
    else if (!v->flg_d_q && !v->flg_s_q)
        v->flg_l_r = 1;
    return (0);
}

int double_redr(int *i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!v->flg_s_q && !v->flg_d_q && sum_flag())
        return (print_error(UN_DR));
    else if ((v->flg_s_q || v->flg_d_q) && ((v->input[*i] *= -1) && (v->input[*i + 1] *= -1)))
        *i += 1;
    if (!v->flg_d_q && !v->flg_s_q && (*i += 1))
        v->flg_d_r = 1;
    return (0);
}