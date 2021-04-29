/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_maker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:25:56 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/29 14:20:31 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstlast_m(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back_m(t_env **alst, t_env *new)
{
	t_env	*p;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	p = ft_lstlast_m(*alst);
	p->next = new;
	new->prev = p;
}

int	ft_lstsize_m(t_env *lst)
{
	int	cp;

	cp = 0;
	while (lst != NULL)
	{
		cp++;
		lst = lst->next;
	}
	return (cp);
}

t_env	*ft_lstnew_m(void *ident, void *value, char equal)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (0);
	new->ident = ident;
	new->value = value;
	new->equal = equal;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_deletenode(t_env **head_ref, t_env *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del->ident);
	free(del->value);
	free(del);
	con.exit_stat = 0;
}
