/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:32:39 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/03 16:01:13 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_array(char ***tab)
{
	int		i;
	int		j;
	int		count;
	char	**tmp;
	char	*swp;

	tmp = *tab;
	i = -1;
	count = 0;
	while (tmp[count])
		count++;
	while (++i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
			{
				swp = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = swp;
			}
			j++;
		}
	}
}

void	store_var_env(t_global *m_gl, char *str)
{
	char	**arg;
	t_env	*new;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	arg = ft_split(str, '=');
	if (ft_strchr(str, '='))
		new = ft_lstnew_m(ft_substr(str, 0, i),
				ft_substr(str, i + 1, ft_strlen(str)), '=');
	if (!ft_strchr(str, '='))
		new = ft_lstnew_m(ft_substr(str, 0, i), NULL, 0);
	ft_lstadd_back_m(&(m_gl->envar), new);
	free_tab(arg);
	con.exit_stat = 0;
}

int	search_vr(t_global *m_gl, char *str)
{
	t_env	*env_l;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	env_l = m_gl->envar;
	tmp = ft_substr(str, 0, i);
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, tmp))
		{
			env_l->equal = 0;
			if (ft_strchr(str, '='))
				env_l->equal = '=';
			free(env_l->value);
			env_l->value = ft_substr(str, i + 1, ft_strlen(str));
			free(tmp);
			return (1);
		}
		env_l = env_l->next;
	}
	free(tmp);
	return (0);
}

void	export_main(t_global *m_gl, char **tab)
{
	int		opt;
	char	**arg;
	int		i;

	i = 0;
	opt = check_exp(tab);
	arg = put_in_tab(m_gl);
	sort_array(&arg);
	if (opt == 1)
	{
		while (arg[i] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(arg[i++], 1);
		}
	}
	else
		export_affect(m_gl, tab);
	free_tab(arg);
}

void	export_affect(t_global *m_gl, char **tab)
{
	char	**arg;
	int		i;

	i = 0;
	while (tab[++i])
	{
		arg = ft_split(tab[i], '=');
		if (!ident_val(arg[0]))
		{
			print_err("Minishell: export: `%s': not a valid identifier\n",
				tab[i], 1);
		}
		else if (!search_vr(m_gl, tab[i]))
			store_var_env(m_gl, tab[i]);
		free_tab(arg);
	}
}
