/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:32:39 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/19 09:59:02 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_exp(char **tab)
{
	int cp;

	cp = 0;
	while (*tab++)
		cp++;
	return (cp);
}

int check_ident(char *tab)
{
	if (ft_isalpha(*tab))
		return 0;
	else
		return 1;
}

char *chartostr(t_env *env_l)
{
	char *str;

	str = malloc(2);
	if (env_l->equal == '=')
		str[0] = '=';
	else
		str[0] = 0;
	str[1] = '\0';
	return (str);
}
void put_qot(t_env *env_l, char **str)
{
	char *tmp;
	char *c;

	c = chartostr(env_l);
	*str = ft_strjoin(env_l->ident, c);
	free(c);
	if (env_l->equal == '=')
	{
		tmp = *str;
		*str = ft_strjoin(*str, "\"");
		free(tmp);
	}
	tmp = *str;
	*str = ft_strjoin(*str, env_l->value);
	free(tmp);
	if (env_l->equal == '=')
	{
		tmp = *str;
		*str = ft_strjoin(*str, "\"");
		free(tmp);
	}
	env_l = env_l->next;
}

char **put_in_tab(t_global *m_gl)
{
	char **tab;
	char *tmp;
	t_env *env_l;
	int i;

	i = 0;
	env_l = m_gl->envar;
	tab = (char **)malloc((ft_lstsize_m(env_l) + 1) * sizeof(char *));
	while (env_l)
	{
		put_qot(env_l, &tab[i]);
		i++;
		env_l = env_l->next;
	}
	tab[i] = NULL;
	return (tab);
}

void sort_array(char ***tab)
{
	int i;
	int j;
	int count;
	char **tmp;
	char *swp;

	tmp = *tab;
	i = 0;
	j = 0;
	count = 0;
	while (tmp[count])
		count++;
	while (i < count - 1)
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
		i++;
	}
}
int count_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void store_var_env(t_global *m_gl, char *str)
{
	char **arg;
	t_env *new;
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	arg = ft_split(str, '=');
	if (ft_strchr(str, '='))
		new = ft_lstnew_m(ft_substr(str, 0, i), ft_substr(str, i + 1, ft_strlen(str)), '=');
	if (!ft_strchr(str, '='))
		new = ft_lstnew_m(ft_substr(str, 0, i), NULL, 0);
	ft_lstadd_back_m(&(m_gl->envar), new);
	free_tab(arg);
}

int search_vr(t_global *m_gl, char *str)
{
	t_env *env_l;
	char *tmp;
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	env_l = m_gl->envar;
	tmp = ft_substr(str, 0, i);
	while (env_l)
	{
		if (!ft_strcmp(env_l->ident, tmp))
		{
			if (ft_strchr(str, '='))
				env_l->equal = '=';
			else
				env_l->equal = 0;
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

void export_main(t_global *m_gl, char **tab)
{
	int opt;
	t_env *tmp;
	t_env *new;
	char **arg;
	int i;

	i = 0;
	tmp = m_gl->envar;
	opt = check_exp(tab);
	arg = put_in_tab(m_gl);
	sort_array(&arg);
	if (opt == 1)
		while (arg[i] != NULL)
		{
			ft_putstr_fd("declare -x ",1);
			ft_putendl_fd(arg[i++], 1);
		}
	else
	{
		free_tab(arg);
		tmp = m_gl->envar;
		arg = ft_split(tab[1], '=');
		if (!ident_val(arg[0]))
		{
			print_err("bash: export: `%s': not a valid identifier\n", tab[1]);
			m_gl->exit_stat = 1;
		}
		else if (!search_vr(m_gl, tab[1]))
			store_var_env(m_gl, tab[1]);
	}
	free_tab(arg);
}