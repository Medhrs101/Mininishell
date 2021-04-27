#include "../minishell.h"

char    *c_in_char(int c)
{
	char *str;

	if (!(str = (char *)malloc(2 * sizeof(char))))
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return(str);
}

void    add_char(t_rdl *rdl, t_hst *tmp, int c)
{
	char *swap;

	tmp->curpos++;
	char *c_str = c_in_char(c);
	swap = ft_strjoin(tmp->old_buff, c_str);
	free(tmp->old_buff);
	tmp->old_buff = swap;
	free(c_str);
	print_line(rdl, tmp);
}

int    hundle_back_n(t_rdl *rdl, t_hst **tmp, t_var *v)
{
	(*tmp)->old_buff[(*tmp)->curpos] = 0;
	if(!(*tmp)->old_buff[0])
	{
		exchange_nodes(tmp);
		delete_node(rdl, *tmp);
		ft_putchar_fd('\n', 0);
		return(0);
	}
	if ((*tmp)->next != NULL)
		exchange_nodes(tmp);
	free((*tmp)->curr_buff);
	(*tmp)->curr_buff = ft_strdup((*tmp)->old_buff);
	swap_curr_old(tmp);
	v->input = ft_strdup((*tmp)->curr_buff);
	ft_putchar_fd('\n', 0);
	return(0);
}

int   hundle_ctrl_c_d(t_rdl *rdl, t_hst **tmp, int pressed_key)
{
	if ((*tmp)->next != NULL)
		exchange_nodes(tmp);
	delete_node(rdl, *tmp);
	ft_putchar_fd('\n', 0);
	if (pressed_key == CTRL_C)
		return(0);
	else
		exit(0);
	return(1);
}

int     up_or_down(t_rdl *rdl, int pressed_key, t_hst **tmp)
{
	if (pressed_key != KEYCODE_U && pressed_key != KEYCODE_D)
		return (0);
	else if (pressed_key == KEYCODE_U)
	{
		if ((*tmp)->prev == NULL)
			return(0);
		*tmp = (*tmp)->prev;
		print_line(rdl, *tmp);
	}
	else if (pressed_key == KEYCODE_D)
	{
		if ((*tmp)->next == NULL)
			return(0);
	   *tmp = (*tmp)->next;
		if((*tmp)->next == NULL)
		{
			free((*tmp)->curr_buff);
			(*tmp)->curr_buff = ft_strdup((*tmp)->old_buff);
		}
		print_line(rdl, *tmp);
	}
	return (1);
}