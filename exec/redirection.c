/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:37:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/08 14:09:43 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void out_red(t_var *var)
{
	t_file *file;
	int fd;
	int	fd2;

	fd = 0;
	fd2 = 0;
	file = var->node->file;
	while (file)
	{
		if (file->type == '>')
		{
			fd = open(file->name_file, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		file = file->next;
	}
	dup2(fd, 1);
}