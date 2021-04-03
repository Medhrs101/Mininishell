/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:07:16 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/01 10:17:13 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env_main(t_global *m_gl, char **tab)
{
	t_env *tmp;

	tmp = m_gl->envar;
	while (tmp)
	{
		printf("%s%c%s\n", tmp->ident, tmp->equal, tmp->value);
		tmp = tmp->next;
	}
}