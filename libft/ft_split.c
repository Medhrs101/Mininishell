/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 19:32:11 by moharras          #+#    #+#             */
/*   Updated: 2021/04/29 17:17:25 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	bad_spot(char **tab, int i)
// {
// 	while (i)
// 	{
// 		free(tab[i]);
// 		i--;
// 	}
// 	free(tab);
// }

// int	c_split(char const *str, char c)
// {
// 	int	i;
// 	int	cp_word;
// 	int	is_num;

// 	is_num = 0;
// 	cp_word = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			is_num = 0;
// 		else
// 		{
// 			if (is_num == 0)
// 			{
// 				cp_word++;
// 				is_num = 1;
// 			}
// 		}
// 		i++;
// 	}
// 	return (cp_word);
// }

// char	*p_split(char const *str, int *n, char c)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*split;

// 	i = *n;
// 	while (str[i] == c)
// 		i++;
// 	start = i;
// 	while (str[i] != c && str[i])
// 		i++;
// 	end = i;
// 	*n = end;
// 	split = (char *)malloc(end - start + 1);
// 	if (!split)
// 		return (NULL);
// 	i = 0;
// 	while (start < end)
// 	{
// 		split[i] = str[start];
// 		i++;
// 		start++;
// 	}
// 	split[i] = '\0';
// 	return (split);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	int		pos;
// 	char	**split_t;

// 	if (s == NULL)
// 		return (NULL);
// 	split_t = (char **)malloc((1 + c_split(s, c)) * sizeof(char *));
// 	if (split_t == NULL)
// 		return (NULL);
// 	i = 0;
// 	pos = 0;
// 	while (i < c_split(s, c))
// 	{
// 		split_t[i] = p_split(s, &pos, c);
// 		if (!split_t[i])
// 		{
// 			bad_spot(split_t, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	split_t[i] = NULL;
// 	return (split_t);
// }

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