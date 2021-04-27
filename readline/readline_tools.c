#include "../minishell.h"

void    init_term()
{
	char    *term_type;
	int     ret;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_putstr_fd ("TERM must be set (see 'env').\n", 1);
		exit (0);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_putstr_fd("Could not access to the termcap database..\n", 1);
		exit (0);
	}
	else if (ret == 0)
	{
		ft_putstr_fd("Terminal type 'TERM' is not defined in termcap database (or have too few informations).\n", 1);
		exit (0);
	}
}

void    exchange_nodes(t_hst **tmp)
{
	int curpos = (*tmp)->curpos;
	char *old_buff = NULL;
	old_buff = ft_strdup((*tmp)->old_buff);
	free((*tmp)->old_buff);
	(*tmp)->old_buff = ft_strdup((*tmp)->curr_buff);
	(*tmp)->curpos = ft_strlen((*tmp)->old_buff);
	while((*tmp)->next)
		*tmp = (*tmp)->next;
	(*tmp)->curpos = curpos;
	free((*tmp)->old_buff);
	(*tmp)->old_buff = old_buff;
}

void delete_node(t_rdl *rdl, t_hst *tmp)
{
	free(tmp->curr_buff);
	free(tmp->old_buff);
	if (rdl->head == NULL || tmp == NULL)
		return;
	if (rdl->head == tmp)
		rdl->head = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	free(tmp);
	return;
}

void swap_curr_old(t_hst **tmp)
{
	while((*tmp)->prev)
	{
		free((*tmp)->old_buff);
		(*tmp)->old_buff = ft_strdup((*tmp)->curr_buff);
		(*tmp)->curpos = ft_strlen((*tmp)->curr_buff);
		(*tmp) = (*tmp)->prev;
	}
	free((*tmp)->old_buff);
	(*tmp)->old_buff = ft_strdup((*tmp)->curr_buff);
	(*tmp)->curpos = ft_strlen((*tmp)->curr_buff);
	while((*tmp)->next)
		*tmp = (*tmp)->next;
}