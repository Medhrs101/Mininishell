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
    v->ambiguous = NULL;

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

    con.exit_stat = 0;
    v = get_struct_var(NULL);
    v->flg_d_r = 0;
    v->flg_r_r = 0;
    v->flg_l_r = 0;
    v->flg_p = 0;
    v->flg_s_c = 0;
}

t_var *get_struct_var(t_var *var)
{
    static t_var *tmp;
    if (var)
        tmp = var;
    return (tmp);
}