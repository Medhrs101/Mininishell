/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:34:49 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 14:35:42 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	con.exit_stat = 130;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit: 3", 1);
	con.exit_stat = 131;
}
