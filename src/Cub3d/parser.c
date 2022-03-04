/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:47:00 by tallal--          #+#    #+#             */
/*   Updated: 2022/03/04 14:04:14 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// char	*str_overwrite(char *str, int index)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = index + 1;
// 	while (str && str[j])
// 	{
// 		str[i] = str[j];
// 		j++;
// 		i++;
// 	}
// 	str[i] = '\0';
// }

int	get_next_line(int fd, char **line)
{
	int			ret;
	int			index;
	char		*tmp;
	static char	buff[4097];
	int			i;

	if (!line)
		return (-1);
	*line = NULL;
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
	index = ft_strchr(buff, '\n');
	if (index != -1)
		buff[index] = '\0';
	tmp = *line;
	*line = ft_strjoin(*line, buff);
	if (tmp)
		free(tmp);
	if (*line == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	index++;
	while (buff[index])
	{
		buff[i] = buff[index];
		index++;
		i++;
	}
	buff[i] = '\0';
	return (ret);
}

int	parser(t_info *info, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY));
	if (fd == -1)
		return (0);
}