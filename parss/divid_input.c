#include "../minishell.h"

void    join_cmd_list(t_node *node)
{
    t_node *current;
    t_var *var;

    var = get_struct_var(NULL);
    current = var->node;
    if (current == NULL)
        var->node = node;
    else 
    {
        while(current->link)
            current = current->link;
        current->link = node;
    }
}

void    print_lst()
{
    t_node *current;
    t_var *var;

    var= get_struct_var(NULL);
    current = var->node;
        while(current)
        {
            print_lst_files(current);
            current = current->link;
        }
}

void    inverse_args(char **tab)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while(tab[i])
    {
        j = 0;
        while(tab[i][j])
        {
            if (tab[i][j] < 0)
                tab[i][j] *= -1;
            j++;
        }
        i++;
    }
    // puts("segfault\n");
}

// void    inverse(t_node *node)
// {
//     int     i;

//     i = 0;
//     while(node->cmd[i])
//     {
//         if (node->cmd[i] < 0)
//             node->cmd[i] *= -1;
//         i++;
//     }
//     // puts("segfault\n");
// }


void    stock_cmd(char *str)
{
    t_var   *var;
    t_node *node;
    char    **tab;

    int     i;

    i = 0;
    var = get_struct_var(NULL);
    // printf("||%s||\n", str);
    tab = ft_split(str, '|');
    // print_tab2d(tab);
    while(tab[i])
    {
        node = (t_node *)malloc(sizeof(t_node));
        node->file = NULL;
        node->link = NULL;
        var->str = tab[i];
        // printf("-->{%s}\n", tab[i]);
        search_files(node);
        node->args = ft_split(var->str, ' ');
        inverse_args(node->args);
        node->cmd = node->args[0];
        inverse(node->cmd);
        join_cmd_list(node);
        i++;
    }
    free_tab(tab);
    // print_lst();
}

int     bs_work(char *tab, int s, int d, int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!d && !s)
        return (1);
    else if (d && (tab[i + 1] == '\\' || tab[i + 1] == -34 || tab[i + 1] == '$' || tab[i + 1] == '`'))
    {
        // printf("\n|%c|\n", tab[i + 1]);
        return (1);

    }
    return (0);
}

void    override(char *tab, int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    while(tab[i])
    {
        tab[i] = tab[i + 1];
        i++;
    }
}

void    hundle_s_d(char c, int *s, int *d)
{
    if (c == '"')
        *d = (*d) ? 0 : 1;
    else
        *s = (*s && c == '\'') ? 0 : 1;
}


int    dolar_work(char *tab, int s, int i, int *bs_erno)
{
    if (*bs_erno)
    {
        *bs_erno = 0;
        return(0);
    }
    if(tab[i - 1] == '\\' || s || !tab[i + 1] || tab[i + 1] == '$')
    {
        // printf("{%d}\n", s);
        // puts("\ndolar not work\n");
        return (0);
    }
    return (1);
}

int		isdigit(int c)
{
	if (c <= 57 && c > 48)
		return (1);
	else
		return (0);
}

int     end_dolar(char *tab, int i)
{
    int cpt;

    cpt = 0;
    if (isdigit(tab[i]))
        return (1);
    while(tab[i])
    {
        if (tab[i] < 0 || ft_strrchr("\"|\\'. <>/", tab[i]))
            break;
        cpt++;
        i++;
    }
    return(cpt);
}

// char *get_v_dolar(char *v_dolar)
// {
//     t_env *tmp;
//     t_var *v = get_struct_var(NULL);

//     // tmp = v->m_gl->envar;
//     // printf("||%s||\n", v_dolar);
//     // while(tmp){
//     //     printf("%s=%s\n",tmp->ident, tmp->value );
//     //     tmp = tmp->next;
//     // }
//     while (tmp)
//     {
//         if (!strcmp(v_dolar, tmp->ident))
//             return (tmp->value);
//         tmp = tmp->next;
//     }
//     return (NULL);
// }

char    *get_v_dolar(char *v_dolar)
{
    t_env *tmp;
    t_var *v= get_struct_var(NULL);

    tmp = v->m_gl->envar;
    while(tmp)
    {
        if (!strcmp(v_dolar, tmp->ident))
            return(tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void    bs_hundle(char *tab, int d, int *i, int *bs_erno)
{
    if (tab[*i + 1] == '\\')
    {
        tab[*i] = -92;
        override(tab, *i + 1);
    }
    else
    {
        if (tab[*i + 1] == '$')
            *bs_erno = 1;
        tab[*i + 1] = (tab[*i + 1] != '$' && tab[*i + 1] > 0 && !d) ? -(tab[*i + 1]) : tab[*i + 1];
        override(tab, *i);
        *i -= 1;
    }   
}

void    dolar_hundle(int j, int *i)
{
    t_var *v;
    char *dolar;
    char *v_dolar;
    char *tmp1;
    char *tmp2;
    char *tmp3;
    int k;

    // dolar = NULL;
    // v_dolar = NULL;
    k = 0;
    v = get_struct_var(NULL);

    k = end_dolar(v->sc_sp[j], *i + 1);
    dolar = ft_substr(v->sc_sp[j] , *i + 1, k);
    // v_dolar = get_v_dolar(dolar);
    // printf("{%c,  %d}\n", v->sc_sp[j][*i + 1],v->status);
    v_dolar = (v->sc_sp[j][*i + 1] == '?') ? ft_itoa(v->status) : get_v_dolar(dolar);
    // printf("{%s}\n", v_dolar);
    if (v->sc_sp[j][*i + 1] == '?')
        v->status = 0;
    if (v_dolar != NULL)
    {
        tmp1 = ft_substr(v->sc_sp[j], 0, *i);
        tmp2 = ft_strjoin(tmp1, v_dolar);
        // free(v->tmp1);
        tmp3 = ft_strjoin(tmp2, &v->sc_sp[j][*i + 1 + k]);
        // free(v->tmp2);
        // free(tmp1);
        // tmp1 = NULL;
        // free(tmp2);
        // tmp2 = NULL;
        v->sc_sp[j] = tmp3;
        // free(tmp3);

        tmp3 = NULL;
        *i = *i - 1 + ft_strlen(v_dolar);
        // printf("<-->{%s}\n", v->sc_sp[j]);
    }
    else
    {
        // puts("hallo\n");
        tmp1 = ft_substr(v->sc_sp[j], 0, *i);
        tmp2 = ft_strjoin(tmp1, &v->sc_sp[j][*i + ft_strlen(dolar)+ 1]);
        v->sc_sp[j] = tmp2;
        // free(tmp1);
        // tmp1 = NULL;
        // free(tmp2);
        // tmp2 = NULL;
        // printf("<---->{%s}\n", v->sc_sp[j]);
        *i -= 1;
    }
}

void    hundle_input(int j)
{
    t_var   *v;
    int     i;
    int     s;
    int     d;
    int     bs_erno;

    bs_erno = 0;
    i = -1;
    s = 0;
    d = 0;
    v = get_struct_var(NULL);
    while(v->sc_sp[j][++i])
    {
        if(v->sc_sp[j][i] == '\'' || v->sc_sp[j][i] == '"')
        {
            hundle_s_d(v->sc_sp[j][i], &s, &d);
            override(v->sc_sp[j], i);
            i -= 1;
        }
        else if (v->sc_sp[j][i] == '\\' && bs_work(v->sc_sp[j], s, d, i))
            bs_hundle(v->sc_sp[j], d, &i, &bs_erno);
        else if (v->sc_sp[j][i] == '$' && dolar_work(v->sc_sp[j], s, i, &bs_erno))
            dolar_hundle(j, &i);
    }
}

void    inverse_input(int i)
{
    t_var *v;
    int   j;
    
    v = get_struct_var(NULL);
    j = 0; 
    while(v->sc_sp[i][j])
    {
        if (v->sc_sp[i][j] < 0)
            v->sc_sp[i][j] *= -1;
        j++;
    }
}

void    clear_lst_files(t_node *node)
{
    t_file *current;
    current = node->file;
    if (current == NULL)
        return ;
    else
    {
        while(current)
        {
            // printf ("{tp = |%c| = |%s|}\n", current->type, current->name_file);
            free(current->name_file);
            current = current->next;
        }
        // ft_putstr_fd("\n \033[0;31m   files cleared\n \e[39m", 1);
    }
}

void    clear_lst_cmd_args()
{
    t_node  *current;
    t_var   *var;

    var = get_struct_var(NULL);
    current = var->node;
    if (current == NULL)
    {
        // puts("There is nothing\n");
        return;
    }
    else 
    {
        while(current)
        {
            // puts("clear_cmd\n");
            // puts("------------DATA----------\n");
            // printf("{cmd : |%s|}\n", current->cmd);
            // print_tab2d(current->args);
            // free_tab(current->args);
            clear_lst_files(current);
            // puts("------------DATA----------\n");
            free(current->cmd);
            current = current->link;
        }
        // ft_putstr_fd("\n \033[0;31m   Data cleared \e[39m", 1);
    }
}

void    divid_input()
{
    t_var      *v;
    // char       **tab;
    int         i;

    i = 0;
    v = get_struct_var(NULL);
    v->sc_sp = ft_split(v->input, ';');
    // free(v->input);
        v->stdo = dup(1);
    while(v->sc_sp[i])
    {
        hundle_input(i);
        v->node = NULL;
        stock_cmd(v->sc_sp[i]);
        // free(v->sc_sp[i]);
        //---------------------
        // out_red(v);
        execute(v->m_gl,v->node);
        dup2(v->stdo, 1);
        close(v->stdo);
        //---------------------
        clear_lst_cmd_args();
        i++;
    }
    // free(v->sc_sp);
}