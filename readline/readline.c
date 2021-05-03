/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:24:22 by moharras          #+#    #+#             */
/*   Updated: 2021/05/03 15:07:56 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_input(t_var *v, t_rdl *rdl, t_hst *tmp)
{
	int		pressed_key;

	pressed_key = 0;
	insert_at_tail(rdl, tmp);
	while (tmp->next)
		tmp = tmp->next;
	while (1)
	{
		pressed_key = 0;
		read(0, &pressed_key, 4);
		if (up_or_down(rdl, pressed_key, &tmp))
			continue ;
		else if (ft_isprint(pressed_key))
			add_char(rdl, tmp, pressed_key);
		else if (pressed_key == CTRL_D && !tmp->curpos)
			hundle_ctrl_c_d(rdl, &tmp, pressed_key);
		else if (pressed_key == CTRL_C
			&& !hundle_ctrl_c_d(rdl, &tmp, pressed_key))
			break ;
		else if (pressed_key == 127 && tmp->old_buff[0])
			delete_char(tmp);
		else if (pressed_key == '\n' && !hundle_back_n(rdl, &tmp, v))
			break ;
	}
}

void	get_coord_cursor(t_rdl *rdl)
{
	char	*buff;
	char	ch;
	int		i;

	buff = (char *)malloc(sizeof(char) * 20);
	i = 0;
	ch = 0;
	write(0, "\033[6n", 4);
	while (ch != 'R')
	{
		read(0, &ch, 1);
		buff[i] = ch;
		i++;
	}
	i = 2;
	if (ft_isdigit(buff[i]))
		rdl->start.y = ft_atoi(&buff[i]);
	while (ft_isdigit(buff[i]))
		i++;
	rdl->start.x = ft_atoi(&buff[i + 1]);
	free(buff);
}

void	initial_terminal(struct termios *oldattr)
{
	struct termios	attr;

	tcgetattr(0, oldattr);
	attr = *oldattr;
	attr.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, &attr);
}

void	ft_readline(t_rdl *rdl)
{
	t_var			*v;
	t_hst			*tmp;
	struct termios	oldattr;

	rdl->k = 0;
	tmp = get_new_node();
	v = get_struct_var(NULL);
	initial_terminal(&oldattr);
	get_input(v, rdl, tmp);
	rdl->k = 0;
	oldattr.c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, &oldattr);
}
