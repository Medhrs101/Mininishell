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
        print_tab2d(current->args);
        // print_lst_files(current);
        current = current->link;
    }
}

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

int     ft_argchr(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] != ' ')
            return(1);
        i++;
    }
    return (0);
}

t_node    *create_node(t_node *node)
{
        node = (t_node *)malloc(sizeof(t_node));
        node->file = NULL;
        node->link = NULL;
        node->cmd = NULL;
        return(node);
}
void    stock_cmd(char *str, t_var *v)
{
    t_node  *node;
    char    **tb;
    int     i;

    i = 0;
    tb = ft_split(str, '|');
    while(tb[i])
    {
        node = create_node(node);
        v->str = ft_strdup(tb[i]);
        search_files(node);
        if(!ft_argchr(v->str))
            node->cmd = NULL;
        else
        {
            // printf(">%s<", v->str);
            node->args = ft_split(v->str, ' ');
            inverse_args(node->args);
            node->cmd = node->args[0];
            inverse(node->cmd);
        }
        join_cmd_list(node);
        free(v->str);
        i++;
    }
    free_tab(tb);
}

int     bs_work(char *tb, t_hp *t)
{
    t_var *v;

    v = get_struct_var(NULL);
    if (!t->d && !t->s)
    {
        if (t->r == 1)
         t->r = 0;
        return (1);
    }
    else if (t->d && (tb[t->i + 1] == '\\' || tb[t->i + 1] == -34 || tb[t->i + 1] == '$' || tb[t->i + 1] == '`'))
    {
        if (t->r == 1)
         t->r = 0;
        return (1);

    }
    return (0);
}

void    override(char *tb, int i)
{
    t_var *v;

    v = get_struct_var(NULL);
    while(tb[i])
    {
        tb[i] = tb[i + 1];
        i++;
    }
}

int    dolar_work(char *tb, t_hp *t)
{
    if (t->bs_erno)
    {
        t->bs_erno = 0;
        return(0);
    }
    if(tb[t->i - 1] == '\\' || t->s || !tb[t->i + 1] || tb[t->i + 1] == '$')
        return (0);
    return (1);
}

int		isdigit(int c)
{
	if (c <= 57 && c > 48)
		return (1);
	else
		return (0);
}

int     end_dolar(char *tb, int i)
{
    int cpt;

    cpt = 0;
    if (isdigit(tb[i]))
        return (1);
    while(tb[i])
    {
        // if (tb[i] < 0 || ft_strrchr("\"|\\'. $<>/", tb[i]))
        // if (tb[i] == '0')
        //     return(9);
        if (tb[i] < 0 || ft_strrchr("=~\\/%#{}$*+-.:?@[]^ \"'", tb[i]))
            break;
        cpt++;
        i++;
    }
    return(cpt);
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

void    bs_hundle(char *tb, t_hp *t)
{
    if (tb[t->i + 1] == '\\')
    {
        tb[t->i] = -92;
        override(tb, t->i + 1);
    }
    else
    {
        if (tb[t->i + 1] == '$')
            t->bs_erno = 1;
        tb[t->i + 1] = (tb[t->i + 1] != '$' && tb[t->i + 1] > 0 && !t->d) ? -(tb[t->i + 1]) : tb[t->i + 1];
        override(tb, t->i);
        t->i -= 1;
    }   
}

int     is_red(int c)
{
    t_var *v;
    
    v = get_struct_var(NULL);
    if(c == '>' || c == '<' || c == ' ' || !c)
        return(1);
    return(0);
}

void v_dolar_not_null(t_var *v, int j, t_hp *t)
{
    t->tmp1 = ft_substr(v->sc_sp[j], 0, t->i);
    t->tmp2 = ft_strjoin(t->tmp1, t->v_dolar);
    t->tmp3 = ft_strjoin(t->tmp2, &v->sc_sp[j][t->i + 1 + t->end]);
    free(v->sc_sp[j]);
    v->sc_sp[j] = t->tmp3;
    t->i = t->i - 1 + ft_strlen(t->v_dolar);
    free(t->tmp2);
    free(t->tmp1);
    free(t->v_dolar);
    free(t->dolar);
    if (t->r == 1)
     t->r = 0;   
}

void v_dolar_null(t_var *v, int j, t_hp *t)
{
    if (t->r == 1 && is_red(v->sc_sp[j][t->i + ft_strlen(t->dolar)+ 1]))
    {
        free(t->dolar);
        t->r = 0;
        v->sc_sp[j][t->i] -= 37;
         return ;
    }
    if (t->d == 1 && v->sc_sp[j][t->i + ft_strlen(t->dolar)+ 1] == '"')
    {
        v->sc_sp[j][t->i + ft_strlen(t->dolar)+ 1] -= 36;
        t->d = 0;
    }
    t->tmp1 = ft_substr(v->sc_sp[j], 0, t->i);
    t->tmp2 = ft_strjoin(t->tmp1, &v->sc_sp[j][t->i + ft_strlen(t->dolar)+ 1]);
    free(v->sc_sp[j]);
    v->sc_sp[j] = t->tmp2;
    t->i -= 1;
    free(t->dolar);
    free(t->tmp1);   
}

void     dolar_hundle(int j, t_hp *t)
{
    t_var *v;

    t->end = 0;
    v = get_struct_var(NULL);
    t->end = end_dolar(v->sc_sp[j], t->i + 1);
    t->dolar = ft_substr(v->sc_sp[j] , t->i + 1, t->end);
    if (v->sc_sp[j][t->i + 1] == '?')
        t->v_dolar = ft_itoa(con.exit_stat);
    else
    {
        // if (v->sc_sp[j][t->i + 1] == '0')
        //     t->v_dolar = ft_strdup("00");
        // else
            t->v_dolar = get_v_dolar(t->dolar);
    }
    // printf("%p\n", t->dolar);
    // printf("%p\n", t->v_dolar);
    // printf("%p\n", t->tmp1);
    // printf("%p\n", t->tmp2);
    // printf("%p\n", t->tmp2);
    if (t->v_dolar != NULL)
        v_dolar_not_null(v, j, t);
    else
        v_dolar_null(v, j, t);
}

int     is_redirection(int c, int d, t_hp *t)
{
    if (c == '>' || c == '<' || (c == '>' && d == '>'))
    {
        t->r = 1;
        return (1);
    }
    return (0);
}

void    hp_initial(t_hp *t)
{
    t->bs_erno = 0;
    t->i = -1;
    t->s = 0;
    t->d = 0;
    t->r = 0;
}

void    hundle_s_d(t_var *v, int j, t_hp *t)
{
    if (v->sc_sp[j][t->i] == '"')
    {
        t->d = (t->d) ? 0 : 1;
            if (v->sc_sp[j][t->i + 1] == '"')
            {
                v->sc_sp[j][t->i + 1] -= 36;
                t->d = 0;
                t->r = 0;
            }
    }
    else
        t->s = (t->s && v->sc_sp[j][t->i] == '\'') ? 0 : 1;
    override(v->sc_sp[j], t->i);
    t->i -= 1;
}

int    hundle_input(int j, t_var *v)
{
    t_hp *t;

    t = (t_hp *)malloc(sizeof(t_hp));
    hp_initial(t);
    while(v->sc_sp[j][++t->i])
    {
        if(v->sc_sp[j][t->i] == '\'' || v->sc_sp[j][t->i] == '"')
            hundle_s_d(v, j, t);
        else if (!t->s && !t->d && is_redirection(v->sc_sp[j][t->i], v->sc_sp[j][t->i + 1], t))
        {
            if (v->sc_sp[j][t->i + 1] == '>')
                t->i++;
            else
                continue;
        }
        else if (v->sc_sp[j][t->i] == '\\' && bs_work(v->sc_sp[j], t))
            bs_hundle(v->sc_sp[j], t);
        else if (v->sc_sp[j][t->i] == '$' && dolar_work(v->sc_sp[j], t))
            dolar_hundle(j, t);
        else if (char_off(v->sc_sp[j][t->i]))
        {
            if (t->r == 1)
                t->r = 0;
        }
    }
    free(t);
    return (1);
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
    t_file *tmp;
    current = node->file;
    if (current == NULL)
        return ;
    else
    {
        while(current)
        {
            printf ("{tp = |%c| = |%s|}\n", current->type, current->name_file);
            free(current->name_file);
            // printf("%p\n", current);
            tmp = current;
            current = current->next;
            free(tmp);
        }
        // ft_putstr_fd("\n \033[0;31m   files cleared\n \e[39m", 1);
    }
    // free(current);
}

void    clear_lst_cmd_args()
{
    t_node  *current;
    t_var   *var;
    t_node *tmp;

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
            puts("------------DATA----------\n");
                printf("{cmd : |%s|}\n", current->cmd);
            tmp = current;
            if (current->cmd)
            {
                print_tab2d(current->args);
                free_tab(current->args);
            }
            clear_lst_files(current);
            puts("------------DATA----------\n");
            // tmp = current;
            current = current->link;
            free(tmp);
        }
        // ft_putstr_fd("\n \033[0;31m   Data cleared \e[39m", 1);
    }
    // free(current);
}

void    divid_input()
{
    t_var      *v;
    int         i;

    i = 0;
    v = get_struct_var(NULL);
    v->sc_sp = ft_split(v->input, ';');
    while(v->sc_sp[i])
    {
        hundle_input(i, v);
        // printf("%s\n", v->sc_sp[i]);
        v->node = NULL;
        stock_cmd(v->sc_sp[i], v);
        // printf("%p\n", v->node);
        //---------------------
        v->stdo = dup(STDOUT);
        v->stdi = dup(STDIN);
        // piping(v);
        pip_or_not(v);
        // if (out_red(v))
            // execute(v->m_gl,v->node);
        dup2(v->stdo, STDOUT);
        dup2(v->stdi, STDIN);
        close(v->stdo);
        close(v->stdi);
        //---------------------
        clear_lst_cmd_args();
        i++;
    }
    free_tab(v->sc_sp);
    free(v->input);
}