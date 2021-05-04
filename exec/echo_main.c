/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:04:40 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/04 16:14:04 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_opt(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!i && str[i] != '-')
			return (0);
		else if (i && str[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	if (!ft_strcmp(str, ""))
		return (0);
	return (1);
}

int	check_opt_echo(char **tab)
{
	int	flag;

	flag = 1;
	while (tab[flag])
	{
		if (tab[flag] && check_opt(tab[flag]))
			flag++;
		else
			break ;
	}
	return (--flag);
}

void	echo_main(char **tab)
{
	int	opt;
	int	i;

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
	con.exit_stat = 0;
}
