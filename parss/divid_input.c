#include "../minishell.h"

void	stock_cmd(char *str, t_var *v)
{
	t_node 	*node;
	char	**tb;
	int		i;

	i = 0;
	tb = ft_split(str, '|');
	while (tb[i])
	{
		node = create_node(node);
		v->str = ft_strdup(tb[i]);
		search_files(node);
		if (!ft_argchr(v->str))
			node->cmd = NULL;
		else
		{
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

void	divid_input()
{
	t_var	*v;
	int		i;

	i = 0;
	v = get_struct_var(NULL);
	v->sc_sp = ft_split(v->input, ';');
	while (v->sc_sp[i])
	{
		hundle_input(i, v);
		// printf("%s\n", v->sc_sp[i]);
		v->node = NULL;
		stock_cmd(v->sc_sp[i], v);
		// printf("%p\n", v->node->args);
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