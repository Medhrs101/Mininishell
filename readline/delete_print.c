/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:23:46 by moharras          #+#    #+#             */
/*   Updated: 2021/04/29 12:23:53 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	puts_c(t_hst *tmp)
{
	int	i;

	i = 0;
	while (i < tmp->curpos && tmp->old_buff[i])
	{
		ft_putchar_fd(tmp->old_buff[i], 0);
		i++;
	}
}

int	ft_put(int c)
{
	return (write(0, &c, 1));
}

void	print_line(t_rdl *rdl, t_hst *tmp)
{
	tputs(tgoto(tgetstr("cm", NULL),
			rdl->start.x - 1, rdl->start.y - 1), 0, &ft_put);
	tputs(tgetstr("cd", NULL), 0, &ft_put);
	puts_c(tmp);
}

void	delete_char(t_hst *tmp)
{
	char	*temp;

	ft_putstr_fd("\033[1D\033[K", 0);
	tmp->curpos--;
	tmp->old_buff[tmp->curpos] = 0;
	temp = ft_strdup(tmp->old_buff);
	free(tmp->old_buff);
	tmp->old_buff = temp;
}
