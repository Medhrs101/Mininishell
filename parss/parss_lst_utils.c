#include "../minishell.h"

void	join_cmd_list(t_node *node)
{
	t_node	*current;
	t_var	*var;

	var = get_struct_var(NULL);
	current = var->node;
	if (current == NULL)
		var->node = node;
	else
	{
		while (current->link)
			current = current->link;
		current->link = node;
	}
}

void	print_lst(void)
{
	t_node	*current;
	t_var	*var;

	var = get_struct_var(NULL);
	current = var->node;
	while (current)
	{
		print_tab2d(current->args);
		current = current->link;
	}
}

t_node	*create_node(t_node *node)
{
	node = (t_node *)malloc(sizeof(t_node));
	node->file = NULL;
	node->link = NULL;
	node->cmd = NULL;
	return (node);
}

void	clear_lst_files(t_node *node)
{
	t_file	*current;
	t_file	*tmp;

	current = node->file;
	if (current == NULL)
		return ;
	else
	{
		while (current)
		{
			printf ("{tp = |%c| = |%s|}\n", current->type, current->name_file);
			free(current->name_file);
			tmp = current;
			current = current->next;
			free(tmp);
		}
	}
}

void	clear_lst_cmd_args(void)
{
	t_node	*current;
	t_var	*var;
	t_node	*tmp;

	var = get_struct_var(NULL);
	current = var->node;
	if (current == NULL)
		return ;
	else
	{
		while (current)
		{
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
			current = current->link;
			free(tmp);
		}
	}
}
