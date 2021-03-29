#include "minishell.h"

int    check_line()
{
    int     i;
    t_var   *var;

    var = get_struct_var(NULL);
    i = 0;
    var->input = ft_strtrim(var->input, " ");
    while(var->input[i] && !var->errno)
    {
        off_bs(i);
        if (var->input[i] == '\'')
            simple_quote(i);
        else if (var->input[i] == '"')
            double_quote(i);
        else if (var->input[i] == ';')
        {
            if(behind_s_c(i))
                semi_colone();
        }
        else if (var->input[i] == '|')
            var->errno = pip(i);
        else if (var->input[i] == '>' && var->input[i + 1] == '>')
            var->errno = double_redr(&i);
        else if (var->input[i] == '>')
            var->errno = right_red(i);
        else if (var->input[i] == '<')
            var->errno = left_red(i);
        else if (var->input[i] == '\\')
            b_slash(i);
        else
            caracter(var->input[i], i);
        i++;
    }
    if (var->errno && !(var->errno = 0))
        return (0);
    hundle_end();
    return (0);
}

void    let_start()
{
    int         r;
    t_var       *var;

    var = get_struct_var(NULL);
    var->input = NULL;
    r = 1;
    while (r > 0)
    {
        ft_putstr_fd("Minishell-> ", 1);
        ft_initial();
        // var->input = ft_strdup("cd kj > \" hello ; ' \"");
        if ( (r = get_next_line(0, &var->input)) == -1 )
        {
            free(var->input);
            ft_putstr_fd("ERROR GNL INPUT !!\n",1);
        }
        if (!check_line())
        {
            ft_putstr_fd("------------------------------\n", 1);
            ft_putstr_fd("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$:\n", 1);
        }

    }
}

void 	env_copy(t_var *v, char **env_t)
{
	t_env	*tmp;
	char	**tab;
	char	c;

	v->envar = NULL;
	while (*env_t)
	{
		c = 0;
		tab = ft_split(*env_t++, '=');
		if (tab[1])
			c = '=';
		tmp = ft_lstnew_m(ft_strdup(tab[0]), ft_strdup(tab[1] ? tab[1] : ""), c);
		ft_lstadd_back_m(&(v->envar), tmp);
		free_tab(tab);
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int main(int ac, char **av, char **env)
{
    t_var var;
    t_env *tmp;

    (void)ac;
    (void)av;
    get_struct_var(&var);
    env_copy(&var, env);
    tmp = var.envar;
    // while(tmp)
    // {
    //     printf("|%s|%c|%s|\n", tmp->ident, tmp->equal, tmp->value);
    //     tmp = tmp->next;
    // }
    let_start();
    return (0);
}