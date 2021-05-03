/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:35:34 by moharras          #+#    #+#             */
/*   Updated: 2021/05/03 15:01:09 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	hundle_syntax(t_var *var, int *i)
{
	off_bs(*i);
	if (var->input[*i] == '\'')
		simple_quote(*i);
	else if (var->input[*i] == '"')
		double_quote(*i);
	else if (var->input[*i] == ';')
	{
		if (behind_s_c(*i))
			semi_colone();
		
	}
	else if (var->input[*i] == '|')
		var->erno = pip(*i);
	else if (var->input[*i] == '>' && var->input[*i + 1] == '>')
		var->erno = double_redr(i);
	else if (var->input[*i] == '>')
		var->erno = right_red(*i);
	else if (var->input[*i] == '<')
		var->erno = left_red(*i);
	else if (var->input[*i] == '\\')
		b_slash(*i);
	else
		caracter(var->input[*i], *i);
}

int	check_line(t_var *var)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strtrim(var->input, " ");
	free(var->input);
	var->input = tmp;
	while (var->input[++i] && !var->erno)
		hundle_syntax(var, &i);
	if (var->erno)
	{
		var->erno = 0;
		free(var->input);
		return (0);
	}
	hundle_end();
	return (0);
}

void	mns_loop(t_var *var, t_rdl *rdl)
{
	while (1)
	{
		var->input = NULL;
		ft_putstr_fd("\033[0;32mminishell > \e[39m", 2);
		ft_initial();
		ft_readline(rdl);
		if (var->input && !check_line(var))
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	*var;
	t_rdl	rdl;

	(void)ac;
	(void)av;
	rdl = (t_rdl){0};
	rdl.head = (t_hst *){0};
	var = (t_var *)malloc(sizeof(t_var));
	var->m_gl = (t_global *)malloc(sizeof(t_global));
	get_struct_var(var);
	ft_initial();
	env_copy(var->m_gl, env);
	init_term();
	var->val = get_v_dolar("SHLVL");
	var->shlvl = ft_atoi(var->val) + 1;
	free(var->val);
	change_value("SHLVL", ft_itoa(var->shlvl));
	mns_loop(var, &rdl);
	return (0);
}
