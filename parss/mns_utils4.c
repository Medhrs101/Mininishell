#include "../minishell.h"

void    inverse_args(char **tb)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while(tb[i])
    {
        j = 0;
        while(tb[i][j])
        {
            if (tb[i][j] < 0)
                tb[i][j] *= -1;
            j++;
        }
        i++;
    }
}

char    *get_v_dolar(char *v_dolar)
{
    t_env *tmp;
    t_var *v;
    
    v = get_struct_var(NULL);
    tmp = v->m_gl->envar;
    while(tmp)
    {
        if (!ft_strcmp(v_dolar, tmp->ident))
            return(ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}

void    inverse_file(char *tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        if (tab[0] != -1 && tab[0] != -2 && tab[i] < 0)
            tab[i] *= -1;
        i++;
    }
}

char   *inverse_dolar(char *dolar)
{
    int i;

    i = 0;
    while(dolar[i])
    {
        dolar[i] *= -1;
        i++;
    }
    return(dolar);
}
