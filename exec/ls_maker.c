/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_maker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:25:56 by ymarji            #+#    #+#             */
/*   Updated: 2021/04/01 10:17:13 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *ft_lstlast_m(t_env *lst)
{
	t_env *tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void ft_lstadd_back_m(t_env **alst, t_env *new)
{
	t_env *p;

	if (*alst == NULL)
	{
		*alst = new;
		return;
	}
	p = ft_lstlast_m(*alst);
	p->next = new;
	new->prev = p;
}

int ft_lstsize_m(t_env *lst)
{
	int cp;

	cp = 0;
	while (lst != NULL)
	{
		cp++;
		lst = lst->next;
	}
	return (cp);
}

t_env *ft_lstnew_m(void *ident, void *value, char equal)
{
	t_env *new;

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

int ft_strcmp(const char *s1, const char *s2)
{
	if (!s1)
		return (0 - *(const unsigned char *)s2);
	while (*s1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void ft_lstdelone_m(t_env *lst)
{
	t_env *tmp_p;
	t_env *tmp_n;

	if (lst)
	{
		tmp_p = lst->prev;
		tmp_n = lst->next;
		tmp_p->next = tmp_n;
		tmp_n->prev = tmp_p;
		free(lst);
	}
}

void ft_deletenode(t_env **head_ref, t_env *del)
{
	/* base case */
	if (*head_ref == NULL || del == NULL)
		return;

	/* If node to be deleted is head node */
	if (*head_ref == del)
		*head_ref = del->next;

	/* Change next only if node to be deleted is NOT the last node */
	if (del->next != NULL)
		del->next->prev = del->prev;

	/* Change prev only if node to be deleted is NOT the first node */
	if (del->prev != NULL)
		del->prev->next = del->next;

	/* Finally, free the memory occupied by del*/
	free(del);
	return;
}
