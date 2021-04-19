#include "../minishell.h"

void print_tab2d(char **tab)
{
    int i = 0;
    int j = 0;
    while (tab[i])
    {
        j = 0;
        ft_putchar_fd('{', 1);
        while (tab[i][j])
        {
            ft_putchar_fd(tab[i][j], 1);
            j++;
        }
        ft_putstr_fd("}\n", 1);
        i++;
    }
}

int print_error(int erno)
{
    t_var *v;

    v = get_struct_var(NULL);
    v->erno = erno;
    v->status = 258;
    if (v->erno == NEWLINE)
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
    else if (v->erno == UN_PIPE)
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
    else if (v->erno == UN_LR)
        ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
    else if (v->erno == UN_RR)
        ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
    else if (v->erno == UN_DR)
        ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
    else if (v->erno == UN_SC)
        ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
    else if (v->erno == UN_DSC)
        ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
    else if (v->erno == UN_DPIPE)
        ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
    else if (v->erno == AMB)
    {
        ft_putstr_fd("minishell: $", 2);
        ft_putstr_fd(v->ambiguous, 2);
        ft_putendl_fd(": ambiguous redirect", 2);
        free(v->ambiguous);
        v->ambiguous = NULL;
    }
    return (v->erno);
}

void hundle_end()
{
    t_var *v;

    v = get_struct_var(NULL);
    if (sum_flag() || v->flg_s_q || v->flg_d_q || v->flg_b_s || v->flg_p)
    {
        print_error(NEWLINE);
        return;
    }
    else if (!sum_all_flag(v))
    {
        ft_putstr_fd("we are safe and sound !! \n", 1);
        ft_putstr_fd("------------------------------\n", 1);
        // printf("{%s}\n", v->input);
        // exit(0);
        divid_input();
    }
    else
    {
        //for this moment
        ft_putstr_fd("\nsyntax error near unexpected token  \n", 2);
        ft_putstr_fd(v->input, 1);
    }
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

void caracter(char c, int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (c == ' ' && (v->flg_d_q || v->flg_s_q))
        v->input[i] *= -1;
    if (sum_all_flag() && char_off(c))
        off_flags();
}

int right_red(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!v->flg_s_q && !v->flg_d_q && sum_flag())
        return (print_error(UN_RR));
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

void b_slash(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    // puts("3iw ");
    if (v->flg_s_q)
    {
        v->input[i] *= -1;
        return;
    }
    v->flg_b_s = (v->flg_b_s) ? 0 : 1;
    v->input[i + 1] = (v->flg_b_s && v->input[i + 1] == '"')
    ? -(v->input[i + 1]) : v->input[i + 1];
    v->input[i + 1] = (v->flg_b_s && !v->flg_d_q && (v->input[i + 1] == '\'' || v->input[i + 1] == ';'))
    ? -(v->input[i + 1]) : v->input[i + 1];
}

int double_redr(int *i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!v->flg_s_q && !v->flg_d_q && sum_flag())
        return (print_error(UN_DR));
    else if ((v->flg_s_q || v->flg_d_q) && ((v->input[*i] *= -1) && (v->input[*i + 1] *= -1)))
        *i += 1;
    if (!v->flg_d_q && v->flg_s_c && (*i += 1))
        v->flg_d_r = 1;
    return (0);
}

int pip(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
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

int behind_s_c(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if ((v->flg_s_q || v->flg_d_q) && (v->input[i] *= -1))
        return (0);
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

void semi_colone()
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!v->flg_d_q && !v->flg_s_q)
        v->flg_s_c = 1;
}

void double_quote(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (v->flg_d_q)
    {
        v->flg_d_q = 0;
    }
    else if (v->flg_s_q)
        v->input[i] *= -1;
    else if (!v->flg_d_q && !v->flg_s_q)
    {
        if (sum_all_flag())
            off_flags();
        v->flg_d_q = 1;
    }
}

void off_bs(int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (v->flg_b_s && v->input[i] != '\\')
        v->flg_b_s = 0;
}

void simple_quote(int i)
{
    t_var *v;

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