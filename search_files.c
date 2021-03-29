#include "minishell.h"

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

void    get_file(int i, t_file *file)
{
    t_var   *var;
    int     save_i;
    int     save;
    int     save_end_i;

    var = get_struct_var(NULL);
    save = i;
    save_i = 0;
    save_end_i = 0;
    (var->str[i + 1] == '>') ? i += 2 : i++;
    while(var->str[i])
    {
        if(char_off(var->str[i]) && !save_i)
            save_i = i;
        else if ((var->str[i] == ' ' || var->str[i] == '<' || var->str[i] == '>' || var->str[i] == '>') && save_i)
            break;
        i++;
    }
    if ((!var->str[i] || var->str[i] == ' ' || var->str[i] == '<'||var->str[i] == '>' || var->str[i] == '>') && save_i)
    {
        save_end_i = i;
        file->name_file = ft_substr(var->str, save_i, save_end_i - save_i);
        inverse(file->name_file);
        var->tmp1 = ft_substr(var->str, 0, save);
        var->tmp2 = &var->str[save_end_i];
        var->str = ft_strjoin(var->tmp1, var->tmp2);
        // free(var->tmp1);
        // free(var->tmp2);
    }
}

void    join_file_list(t_node *node, t_file *file)
{
    t_file  *current;
    current = node->file;
    if (current == NULL)
    {
        // ft_putstr_fd("\n||", 1);
        // ft_putstr_fd("   tp = ", 1);
        // ft_putchar_fd(file->type, 1);
        // ft_putstr_fd("   :     ", 1);
        // ft_putstr_fd(file->name_file, 1);
        // ft_putstr_fd("||\n", 1);
        node->file = file;
    }
    else
    {
        while (current->next)
        {

            // ft_putstr_fd("\ndone\n", 1);
            // ft_putstr_fd("\n||", 1);
            // ft_putstr_fd("   tp = ", 1);
            // ft_putchar_fd(file->type, 1);
            // ft_putstr_fd("   :     ", 1);
            // ft_putstr_fd(file->name_file, 1);
            // ft_putstr_fd("||\n", 1);
            current = current->next;
        }
        current->next = file;
    }
}

void    print_lst_files(t_node *node)
{
    t_file *current;
    current = node->file;
    if (current == NULL)
        ft_putstr_fd("There is not file here ", 1);
    else
    {
        while(current)
        {
            ft_putstr_fd("\n||", 1);
            ft_putstr_fd("   tp = ", 1);
            ft_putchar_fd(current->type, 1);
            ft_putstr_fd("   :     ", 1);
            ft_putstr_fd(current->name_file, 1);
            ft_putstr_fd("||\n", 1);
            current = current->next;
        }
        ft_putstr_fd("\n \033[0;31m          ^__^ ^__^ ^__^\e[39m", 1);
    }
}

void    search_files(t_node *node)
{
    t_var   *var = get_struct_var(NULL);
    t_file  *file;
    int     i;
    int     save_i;

    i = 0;
    save_i = 0;
    while(var->str[i])
    {
        if (var->str[i] == '>' &&  var->str[i + 1] == '>')
        {
            file = (t_file *)malloc(sizeof(t_file));
            file->next = NULL;
            file->type = '0';
            file->name_file = NULL;
            file->type = 'a';
            get_file(i, file);
            join_file_list(node, file);
            i = -1;
        }
        else if (var->str[i] == '>')
        {
            file = (t_file *)malloc(sizeof(t_file));
            file->next = NULL;
            file->type = '0';
            file->name_file = NULL;
            file->type = '>';
            get_file(i, file);
             join_file_list(node, file);
            i = -1;
        }
        else if (var->str[i] == '<')
        {
            file = (t_file *)malloc(sizeof(t_file));
            file->next = NULL;
            file->type = '0';
            file->name_file = NULL;
            file->type = '<';
            get_file(i, file);
            join_file_list(node, file);
            i = -1;
        }
        i++;
    }
}