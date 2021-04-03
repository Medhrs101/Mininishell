/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:26:22 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/01 14:22:53 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// void init(t_global *m_gl)
// {
// 	m_gl->home = NULL;
// 	m_gl->exit_stat = 0;
// 	m_gl->stdo = 1;
// 	m_gl->pid = 0;
// 	m_gl->stdi = 0;
// }

// int check_built(t_global *m_gl, char **cmd)
// {
// 	if (cmd[0] && !strcmp(cmd[0], "echo"))
// 		echo_main(m_gl, cmd);
// 	else if (cmd[0] && !strcmp(cmd[0], "cd"))
// 		cd_main(m_gl, cmd);
// 	else if (cmd[0] && !strcmp(cmd[0], "pwd"))
// 		pwd_main(m_gl, cmd);
// 	else if (cmd[0] && !strcmp(cmd[0], "env"))
// 		env_main(m_gl, cmd);
// 	else if (cmd[0] && !strcmp(cmd[0], "export"))
// 		export_main(m_gl, cmd);
// 	else if (cmd[0] && !strcmp(cmd[0], "unset"))
// 		unset(m_gl, cmd);
// 	else if (cmd[0] && !strcmp(cmd[0], "exit"))
// 		exit(0);
// 	else
// 		return (0);
// 	return (1);
// }

// void execute(t_global *m_gl, char *line)
// {
// 	char **tab;
// 	int i;

// 	tab = ft_split(line, ' ');
// 	if (tab[0] && !(i = check_built(m_gl, tab)))
// 		exec_main(m_gl, line);
// 	else if (tab[0] && !i)
// 		print_err("bash: %s: command not found\n", tab[0]);
// 	free_tab(tab);
// }

// void free_tab(char **tab)
// {
// 	int i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

// void modify_path(t_env *env_l)
// {
// 	char *tmp;
// 	char path[PATH_MAX];
// 	char *str;

// 	getcwd(path, PATH_MAX);
// 	str = ft_strjoin(":", path);
// 	tmp = env_l->value;
// 	env_l->value = ft_strjoin(tmp, str);
// 	free(tmp);
// 	free(str);
// }

// void env_copy(t_global *m_gl, char **env_t)
// {
// 	t_env *tmp;
// 	char **tab;
// 	char c;

// 	m_gl->envar = NULL;
// 	while (*env_t)
// 	{
// 		c = 0;
// 		tab = ft_split(*env_t++, '=');
// 		if (tab[1])
// 			c = '=';
// 		tmp = ft_lstnew_m(ft_strdup(tab[0]), ft_strdup(tab[1]), c);
// 		if (!ft_strcmp(tmp->ident, "HOME"))
// 			m_gl->home = ft_strdup(tmp->value);
// 		if (!ft_strcmp(tmp->ident, "PATH"))
// 			modify_path(tmp);
// 		ft_lstadd_back_m(&(m_gl->envar), tmp);
// 		free_tab(tab);
// 	}
// }

int main(int ac, char **av, char **env)
{
	int ret;
	char *line;
	t_global *m_gl = (t_global *)malloc(sizeof(t_global));
	t_env *tmp;

	ret = 0;
	init(m_gl);
	env_copy(m_gl, env);
	while (1)
	{
		ft_putnbr_fd(m_gl->exit_stat, 1);
		ft_putstr_fd("\033[0;31mminishell~> $ : \e[39m", 1);
		ret = get_next_line(0, &line);
		if (ret != 0)
			execute(m_gl, line);
		free(line);
	}
	return 0;
}