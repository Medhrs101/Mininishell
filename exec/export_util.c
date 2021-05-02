/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 14:21:07 by ymarji            #+#    #+#             */
/*   Updated: 2021/05/02 15:33:33 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exp(char **tab)
{
	int	cp;

	cp = 0;
	while (*tab++)
		cp++;
	return (cp);
}

int	check_ident(char *tab)
{
	if (ft_isalpha(*tab))
		return (0);
	else
		return (1);
}

char	*chartostr(t_env *env_l)
{
	char	*str;

	str = malloc(2);
	if (env_l->equal == '=')
		str[0] = '=';
	else
		str[0] = 0;
	str[1] = '\0';
	return (str);
}

void	put_qot(t_env *env_l, char **str)
{
	char	*tmp;
	char	*c;

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

char	**put_in_tab(t_global *m_gl)
{
	char	**tab;
	t_env	*env_l;
	int		i;

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
