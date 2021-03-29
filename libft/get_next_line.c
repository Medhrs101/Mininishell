/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:00:30 by moharras          #+#    #+#             */
/*   Updated: 2021/02/24 16:17:15 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr1(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		len_s;
	char		*sub;
	char		*p_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	p_s = (char *)s;
	i = 0;
	if (len_s < start)
		return (ft_strdup1("\0"));
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && p_s[i + start])
	{
		sub[i] = p_s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char			*ft_strchr1(const char *s, int c)
{
	char		*p_s;
	char		p_c;
	int			i;

	i = 0;
	p_s = (char*)s;
	p_c = (unsigned char)c;
	while (p_s[i])
	{
		if (p_s[i] == p_c)
			return (p_s + i);
		i++;
	}
	if (p_s[i] == '\0' && p_c == '\0')
		return (p_s + i);
	return (NULL);
}

int				func_norm(int fd, char **p, char **line)
{
	int			i;
	char		*t;
	char		*tmp;

	i = 0;
	while (p[fd][i] != '\n' && p[fd][i])
		i++;
	tmp = ft_substr1(p[fd], 0, i);
	free(*line);
	*line = tmp;
	t = p[fd];
	if (p[fd][i] != '\0')
	{
		p[fd] = ft_strdup1(&p[fd][i + 1]);
		free(t);
		return (1);
	}
	else if (p[fd][i] == '\0')
	{
		p[fd] = NULL;
		free(t);
		return (0);
	}
	return (0);
}

int				func_norm_0(char **p, int r, int fd)
{
	(void)p[fd];
	free(p[fd]);
	return (r);
}

int				get_next_line(int fd, char **line)
{
	static char	*p[FD];
	int			r;
	char		*t;
	char		*buff;

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || fd > FD || read(fd, NULL, 0) < 0
		|| !(buff = ((char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	*line = ft_strdup("");
	if (!p[fd])
		p[fd] = ft_strdup("");
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		t = ft_strjoin1(p[fd], buff);
		free(p[fd]);
		p[fd] = t;
		if (ft_strchr1(p[fd], '\n'))
			break ;
	}
	free(buff);
	return (func_norm(fd, p, line));
}
