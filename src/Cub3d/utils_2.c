/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:01:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:05:33 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *str)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == ' '))
			i++;
	size = ft_strlen(str);
	dup = malloc(sizeof(char) * (size + 1 - i));
	if (!dup)
		return (NULL);
	size = i;
	i = 0;
	while (str[size])
	{
		dup[i] = str[size];
		i++;
		size++;
	}
	dup[i] = '\0';
	return (dup);
}

int	get_next_cut(int fd, char **line, char *buff)
{
	int		ret;
	int		index;
	char	*tmp;

	ret = 1;
	index = ft_strchr(buff, '\n');
	while (index == -1)
	{
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		if (tmp)
			free(tmp);
		if (*line == NULL)
			exit(EXIT_FAILURE);
		ret = read(fd, buff, 4096);
		if (ret < 0)
			exit(EXIT_FAILURE);
		if (ret < 4096)
			break ;
		index = ft_strchr(buff, '\n');
	}
	return (ret);
}

void	get_next_cut_2(char *buff, int index)
{
	int	i;

	i = 0;
	while (buff[index])
	{
		buff[i] = buff[index];
		index++;
		i++;
	}
	buff[i] = '\0';
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	int			index;
	char		*tmp;
	static char	buff[4097];

	ret = 1;
	if (!line)
		return (-1);
	*line = NULL;
	ret = get_next_cut(fd, line, buff);
	index = ft_strchr(buff, '\n');
	if (index != -1)
		buff[index] = '\0';
	tmp = *line;
	*line = ft_strjoin(*line, buff);
	if (tmp)
		free(tmp);
	if (*line == NULL)
		exit(EXIT_FAILURE);
	index++;
	get_next_cut_2(buff, index);
	return (ret);
}