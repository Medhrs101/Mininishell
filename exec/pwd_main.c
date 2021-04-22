/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:32:02 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/22 11:09:58 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd_main(t_global *m_gl, char **tab)
{
	char path[PATH_MAX];

	getcwd(path, sizeof(path));
	ft_putendl_fd(path, 1);
	con.exit_stat = 0;
}