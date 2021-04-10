/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:37:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/10 17:29:00 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void out_red()
{
    t_var      *var;
	t_file *file;
	int fd;

    var = get_struct_var(NULL);
	fd = 0;
	file = var->node->file;
	while (file)
	{
		if (file->type == '>')
		{
			fd = open(file->name_file,  O_WRONLY | O_TRUNC | O_CREAT, 0644);
			dup2(fd, 1);
		}
		file = file->next;
	}
}