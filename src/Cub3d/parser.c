/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:47:00 by tallal--          #+#    #+#             */
/*   Updated: 2022/05/16 19:11:55 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
	str = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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

void	put_player(t_info *info, int i, int j, char c)
{
	info->player.spawn_x = j;
	info->player.spawn_y = i;
	info->player.pos.x = j * WALL_W + WALL_W / 2;
	info->player.pos.y = i * WALL_H + WALL_H / 2;
	if (c == 'N')
		info->player.rotation = PI / 2;
	else if (c == 'S')
		info->player.rotation = -PI / 2;
	else if (c == 'E')
		info->player.rotation = 0;
	else
		info->player.rotation = PI;
}

int	player_spawn(t_info *info, char **map_txt)
{
	int	i;
	int	j;
	int	check_double;

	i = 0;
	check_double = 0;
	while (map_txt[i])
	{
		j = 0;
		while (map_txt[i][j])
		{
			if (map_txt[i][j] == 'N' || map_txt[i][j] == 'S'
				|| map_txt[i][j] == 'E' || map_txt[i][j] == 'W')
			{
				put_player(info, i, j, map_txt[i][j]);
				check_double++;
				map_txt[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (!check_double || check_double > 1)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	int			index;
	char		*tmp;
	static char	buff[4097];
	int			i;

	ret = 1;
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

int	tablen(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**tabjoin(char **tab, char *str)
{
	char	**newtab;
	int		i;

	newtab = ft_calloc(sizeof(char *) * (tablen(tab) + 2));
	if (!newtab)
		fatal_error();
	i = 0;
	while (tab && tab[i])
	{
		newtab[i] = tab[i];
		i++;
	}
	newtab[i] = str;
	newtab[i + 1] = NULL;
	free(tab);
	return (newtab);
}

int	map_char_to_int(char c)
{
	if (c == '0')
		return (0);
	else if (c == '1')
		return (1);
	else if (c == ' ')
		return (2);
	else
		return (-1);
}

int	**fill_map_int(char **map_txt, int line_len, int nb_line)
{
	int	**map_int;
	int	i;
	int	j;

	map_int = ft_calloc(sizeof(int *) * (nb_line + 1));
	if (!map_int)
		fatal_error();
	i = 0;
	while (map_txt[i])
	{
		map_int[i] = ft_calloc(sizeof(int) * (line_len));
		if (!map_int[i])
			fatal_error();
		j = 0;
		while (j < line_len)
		{
			if (j < ft_strlen(map_txt[i]))
				map_int[i][j] = map_char_to_int(map_txt[i][j]);
			else
				map_int[i][j] = 2;
			j++;
		}
		i++;
	}
	map_int[i] = NULL;
	return (map_int);
}

int		valid_zero(int **map_int, int i, int j, int line_len)
{
	int	nb_line;

	nb_line = tablen((char **)map_int);
	if (i == 0 || i == nb_line - 1)
		return (0);
	if (j == 0 || j == line_len -1)
		return (0);
	if (map_int[i][j - 1] == 2)
		return (0);
	if (map_int[i][j + 1] == 2)
		return (0);
	if (map_int[i - 1][j] == 2)
		return (0);
	if (map_int[i + 1][j] == 2)
		return (0);
	return (1);
}

int		check_map(int **map_int, int line_len)
{
	int	i;
	int	j;

	i = 0;
	while (map_int[i])
	{
		j = 0;
		while (j < line_len)
		{
			if (map_int[i][j] == -1)
				return (-1);
			if (map_int[i][j] == 0 && !valid_zero(map_int, i, j, line_len))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_map(t_info *info, int **map_int, int line_len, int nb_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_line)
	{
		j = 0;
		while (j < line_len)
		{
			if (map_int[i][j] == 1)
			{
				info->map[i * line_len + j].is_wall = 1;
				info->map[i * line_len + j].is_void = 1;
			}
			else if (map_int[i][j] == 0)
			{
				info->map[i * line_len + j].is_void = 0;
				info->map[i * line_len + j].is_wall = 0;
			}
			else
				info->map[i * line_len + j].is_wall = 1;
			info->map[i * line_len + j].rect.w = WALL_W;
			info->map[i * line_len + j].rect.h = WALL_H;
			info->map[i * line_len + j].rect.x = j * WALL_W;
			info->map[i * line_len + j].rect.y = i * WALL_H;
			j++;
		}
		i++;
	}
	deltab((char **)map_int);
}

int		parse_map(t_info *info, char **map_txt)
{
	int	**map_int;
	int	line_len;
	int	i;

	line_len = 0;
	i = 0;
	while (map_txt[i])
	{
		if (ft_strlen(map_txt[i]) > line_len)
			line_len = ft_strlen(map_txt[i]);
		i++;
	}
	map_int = fill_map_int(map_txt, line_len, i);
	if (check_map(map_int, line_len) == -1)
		ft_exit(info, 1, map_int, map_txt);
	fill_map(info, map_int, line_len, i);
	deltab(map_txt);
	return (0);
}

t_info	*create_info(char **map_txt)
{
	int	i;
	int	w;
	int	h;

	h = tablen(map_txt);
	i = 0;
	w = 0;
	while (map_txt[i])
	{
		if (ft_strlen(map_txt[i]) > w)
			w = ft_strlen(map_txt[i]);
		i++;
	}
	if (w == 0 || h == 0)
		return (NULL);
	return (init_info(w, h));
}

t_info	*parser(char *file)
{
	int		fd;
	char	*line;
	char	**map_txt;
	t_info	*info;

	map_txt = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
		map_txt = tabjoin(map_txt, line);
	free(line);
	info = create_info(map_txt);
	player_spawn(info, map_txt);
	if (parse_map(info, map_txt) < 0)
		return (NULL);
	return (info);
}
