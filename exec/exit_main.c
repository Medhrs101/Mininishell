/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:03:04 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 14:17:13 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_arg(char **cmd)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (i > 1)
			return (-2);
	}
	if (cmd[1])
	{
		if (cmd[1][j] == '-' || cmd[1][j] == '+')
			j++;
		while (cmd[1][j])
			if (!ft_isdigit(cmd[1][j++]))
				return (-1);
		count = ft_strlen(cmd[1]);
		if (count > 19 || (count == 19 && cmd[1][count] > '7'))
			return (-1);
	}
	return (1);
}

void	free_env(t_env *env_l)
{
	while (env_l)
	{
		free(env_l->ident);
		free(env_l->value);
		free(env_l);
		env_l = env_l->next;
	}
}

void	exit_stat(int stat, t_env *env_l, char **cmd)
{
	int	i;

	ft_putendl_fd("exit", 2);
	i = exit_arg(cmd);
	if (i == -2)
		print_err("bash: exit: too many arguments\n", cmd[1], 1);
	if (i == -1)
	{
		print_err("bash: exit: %s: numeric argument required\n", cmd[1], 255);
		free_env(env_l);
		exit(255);
	}
	if (i != -2)
	{
		free_env(env_l);
		if (cmd[1] && i != -1)
		{
			i = ft_atoi_l(cmd[1]);
			clear_lst_cmd_args();
			exit(i);
		}
		clear_lst_cmd_args();
		exit(stat);
	}
}
