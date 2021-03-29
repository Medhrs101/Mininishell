/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 19:32:11 by moharras          #+#    #+#             */
/*   Updated: 2019/11/09 18:50:43 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**leak_split(char **t, int r)
{
	while (r != 0)
	{
		free(t[r]);
		r--;
	}
	free(t);
	return (NULL);
}

static int		ft_motnumber(char *str, char c)
{
	int		i;
	int		alpha;

	i = 0;
	alpha = 0;
	while (str[i])
	{
		if (str[i] != c)
			alpha++;
		while (str[i + 1] && str[i] != c)
			i++;
		i++;
	}
	return (alpha);
}

static int		ft_motlength(char *str, char c)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i])
	{
		length++;
		i++;
	}
	return (length);
}

char			**ft_split(char const *s, char c)
{
	int			i;
	int			j;
	int			n;
	char		**t;
	int			len;

	i = 0;
	n = 0;
	if (!s || !(t = (char **)
				malloc(sizeof(char*) * (ft_motnumber((char*)s, c) + 1))))
		return (NULL);
	while (i < ft_motnumber((char*)s, c))
	{
		len = ft_motlength(((char*)s + n), c) + 1;
		if (!(t[i] = (char *)malloc(sizeof(char) * len)))
			return (leak_split(t, i));
		j = 0;
		while (s[n] == c)
			n++;
		while (s[n] != c && s[n])
			t[i][j++] = s[n++];
		t[i++][j] = '\0';
	}
	t[i] = NULL;
	return (t);
}
