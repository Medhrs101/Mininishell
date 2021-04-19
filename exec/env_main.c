/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:07:16 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/18 17:09:01 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_main(t_global *m_gl, char **tab)
{
	t_env *tmp;

	tmp = m_gl->envar;
	while (tmp)
	{
		ft_putstr_fd(tmp->ident,1);
		ft_putchar_fd(tmp->equal, 1);
		ft_putendl_fd(tmp->value,1);
		// printf("%s%c%s\n", tmp->ident, tmp->equal, tmp->value);
		tmp = tmp->next;
	}
}