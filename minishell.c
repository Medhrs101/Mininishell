#include "./minishell.h"

int check_line()
{
	int i;
	t_var *var;
	char *tmp;
	var = get_struct_var(NULL);
	i = 0;
	tmp = ft_strtrim(var->input, " ");
	free(var->input);
	var->input = tmp;
	while (var->input[i] && !var->erno)
	{
		off_bs(i);
		if (var->input[i] == '\'')
			simple_quote(i);
		else if (var->input[i] == '"')
			double_quote(i);
		else if (var->input[i] == ';')
		{
			if (behind_s_c(i))
				semi_colone();
		}
		else if (var->input[i] == '|')
			var->erno = pip(i);
		else if (var->input[i] == '>' && var->input[i + 1] == '>')
			var->erno = double_redr(&i);
		else if (var->input[i] == '>')
			var->erno = right_red(i);
		else if (var->input[i] == '<')
			var->erno = left_red(i);
		else if (var->input[i] == '\\')
			b_slash(i);
		else
			caracter(var->input[i], i);
		i++;
	}
	if (var->erno && !(var->erno = 0))
		return (0);
	hundle_end();
	return (0);
}

// void let_start()
// {
// 	int r;
// 	t_var *var;

// 	var = get_struct_var(NULL);
// 	var->input = NULL;
// 	r = 1;
// 	var->status = 0;
// 	var->shlvl = ft_atoi(get_v_dolar("SHLVL")) + 1;
// 	change_value("SHLVL", ft_itoa(var->shlvl));
// 	while (r > 0)
// 	{
// 		ft_putstr_fd("\033[0;31mminishell~> $ : \e[39m", 1);
// 		ft_initial();
// 		// var->input = ft_strdup("ls");
// 		if ((r = get_next_line(0, &var->input)) == -1)
// 		{
// 			free(var->input);
// 			ft_putstr_fd("ERROR GNL INPUT !!\n", 1);
// 		}
// 		if (!check_line())
// 		{
// 			ft_putstr_fd("------------------------------\n", 1);
// 			ft_putstr_fd("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$:\n", 1);
// 		}
// 	}
// }

// void env_copy(t_var *v, char **env_t)
// {
//     t_env *tmp;
//     char **tab;
//     char c;

//     v->envar = NULL;
//     while (*env_t)
//     {
//         c = 0;
//         tab = ft_split(*env_t++, '=');
//         if (tab[1])
//             c = '=';
//         tmp = ft_lstnew_m(ft_strdup(tab[0]), ft_strdup(tab[1] ? tab[1] : ""), c);
//         ft_lstadd_back_m(&(v->envar), tmp);
//         free_tab(tab);
//     }
// }

void free_tab(char **tab)
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
	t_var *var;
	// t_env *tmp;
	t_rdl rdl;

	(void)ac;
	(void)av;

    rdl = (t_rdl){0};
    // rdl = (t_rdl *)malloc(sizeof(t_rdl));
    rdl.head = (t_hst *){0};
    // rdl.head = NULL;

	var = (t_var *)malloc(sizeof(t_var));
	var->m_gl = (t_global *)malloc(sizeof(t_global));
	get_struct_var(var);
	env_copy(var->m_gl, env);
    init_term();
	var->val = get_v_dolar("SHLVL");
	var->shlvl = ft_atoi(var->val) + 1;
	free(var->val);
	change_value("SHLVL", ft_itoa(var->shlvl));
 	while(1)
    {
		var->input = NULL;
        // tputs(tparm(tgetstr("AF", NULL), COLOR_GREEN), 0, &ft_put);
        // ft_putstr_fd ("minishell > ", 1);
        // tputs(tparm(tgetstr("me", NULL), COLOR_GREEN), 0, &ft_put);
        // tputs(tgetstr("cd", NULL), 0, &ft_put);
		ft_putstr_fd("\033[0;32mminishell > \e[39m", 0);
		ft_initial();
        ft_readline(&rdl);
		// var->input = ft_strdup("echo hello");
		if (var->input && !check_line())
		{
			ft_putstr_fd("------------------------------\n", 1);
			ft_putstr_fd("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$:\n", 1);
		}
    }
    return(0);
}