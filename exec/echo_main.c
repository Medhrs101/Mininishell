/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:04:40 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/02 17:32:51 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_opt_echo(char **tab)
{
	int flag;

	flag = 1;
	while (tab[flag])
		if (tab[flag] && !ft_strncmp(tab[flag], "-n", ft_strlen(tab[flag])))
			flag++;
		else
			break;
	return --flag;
}

void echo_main(t_global *m_gl, char **tab)
{
	int opt;
	int i;

	opt = check_opt_echo(tab);
	i = 1 + opt;
	while (tab[i])
	{
		if (i - 1 != opt)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(tab[i++], 1);
	}
	if (opt == 0)
		ft_putstr_fd("\n", 1);
}