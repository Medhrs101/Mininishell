#include "../minishell.h"

t_var	*get_struct_var(t_var *var)
{
	static t_var	*tmp;

	if (var)
		tmp = var;
	return (tmp);
}

void	off_bs(int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (v->flg_b_s && v->input[i] != '\\')
		v->flg_b_s = 0;
}

void	caracter(char c, int i)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (c == ' ' && (v->flg_d_q || v->flg_s_q))
		v->input[i] *= -1;
	if (sum_all_flag() && char_off(c))
		off_flags();
}

void	hp_initial(t_hp *t)
{
	t->bs_erno = 0;
	t->i = -1;
	t->s = 0;
	t->d = 0;
	t->r = 0;
}

int	is_red(int c)
{
	t_var	*v;

	v = get_struct_var(NULL);
	if (c == '>' || c == '<' || c == ' ' || !c)
		return (1);
	return (0);
}
