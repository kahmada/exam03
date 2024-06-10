/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:40:18 by kahmada           #+#    #+#             */
/*   Updated: 2024/06/05 16:42:46 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

#endif


int	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc ((len1 + len2 + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
		new[i++] = s1[j++];
	j = 0;
	while (j < len2)
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*kast;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	kast = (char *)malloc((len + 1) * sizeof(char));
	if (!kast)
		return (NULL);
	while (s[start] && i < len)
	{
		kast[i++] = s[start++];
	}
	kast[i] = '\0';
	return (kast);
}

char	*make_stock(char *str)
{
	int		i;
	char	*stock;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			stock = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = NULL;
			return (stock);
		}
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

char	*ft_extract(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (ft_substr(str, 0, i + 1));
}

char	*read_from_fd(int fd, char **str)
{
	char	*buf;
	int		nbyt_read;
	int		nl_position;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	nbyt_read = 1;
	while (nbyt_read)
	{
		nbyt_read = read(fd, buf, BUFFER_SIZE);
		if (nbyt_read < 0)
			return (free(*str), *str = NULL, NULL);
		buf[nbyt_read] = '\0';
		*str = ft_strjoin(*str, buf);
		nl_position = ft_check(buf);
		if (nl_position != -1)
			break ;
	}
	free(buf);
	buf = NULL;
	return (*str);
}


char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
		return (free(str), str = NULL, NULL);
	str = read_from_fd(fd, &str);
	if (!str || !str[0])
		return (free(str), str = NULL, NULL);
	line = ft_extract(str);
	if (!line || !line[0])
		return (free(str), str = NULL, NULL);
	str = make_stock(str);
	return (line);
}