#include "../minishell.h"

void    inverse(char *tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        if (tab[i] < 0)
            tab[i] *= -1;
        i++;
    }
}

void    stock_name_file(int i, int save_i, int save, t_file *file)
{
    int save_end_i;
    char    *tmp1;
    char    *tmp2;
    t_var   *v;

    v = get_struct_var(NULL);
    save_end_i = i;
    file->name_file = ft_substr(v->str, save_i, save_end_i - save_i);
    inverse_file(file->name_file);
    tmp1 = ft_substr(v->str, 0, save);
    tmp2 = ft_strdup(&v->str[save_end_i]);
    free(v->str);
    v->str = ft_strjoin(tmp1, tmp2);
    free(tmp1);
    free(tmp2);
}

void    get_file(t_var *v, int i, t_file *file)
{
    int     save_i;
    int     save;


    save = i;
    save_i = 0;
    (v->str[i + 1] == '>') ? i += 2 : i++;
    while(v->str[i])
    {
        if((char_off(v->str[i]) || v->str[i] < 0) && !save_i)
            save_i = i;
        else if ((v->str[i] == ' ' || v->str[i] == '<' || v->str[i] == '>' || v->str[i] == '>') && save_i)
            break;
        i++;
    }
    if ((!v->str[i] || v->str[i] == ' ' || v->str[i] == '<'||v->str[i] == '>' || v->str[i] == '>') && save_i)
        stock_name_file(i, save_i, save, file);
}

void    join_file_list(t_node *node, t_file *file)
{
    t_file  *current;
    current = node->file;
    if (current == NULL)
        node->file = file;
    else
    {
        while (current->next)
            current = current->next;
        current->next = file;
    }
}

void create_node_file(t_node *node, t_file *file, int *i, int c)
{
    t_var   *v;

    v = get_struct_var(NULL);
    file = (t_file *)malloc(sizeof(t_file));
    file->next = NULL;
    file->type = '0';
    file->name_file = NULL;
    file->type = c;
    get_file(v, *i, file);
    join_file_list(node, file);
    *i = -1;
}

void    search_files(t_node *node)
{
    t_var   *var = get_struct_var(NULL);
    t_file  *file;
    int     i;

    i = 0;
    while(var->str[i])
    {
        if (var->str[i] == '>' &&  var->str[i + 1] == '>')
            create_node_file(node, file, &i, 'a');
        else if (var->str[i] == '>')
            create_node_file(node, file, &i, '>');
        else if (var->str[i] == '<')
            create_node_file(node, file, &i, '<');
        i++;
    }
}