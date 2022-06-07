/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:45:44 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/07 15:48:49 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

t_info	*create_info(char **map_txt, char **sprites)
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
	return (init_info(w, h, sprites, map_txt));
}

char	check_char(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	if (str[*i] && str[(*i) + 1])
	{
		if (str[*i] == 'N' && str[(*i) + 1] == 'O')
			return ('N');
		else if (str[*i] == 'S' && str[(*i) + 1] == 'O')
			return ('S');
		else if (str[*i] == 'W' && str[(*i) + 1] == 'E')
			return ('W');
		else if (str[*i] == 'E' && str[(*i) + 1] == 'A')
			return ('E');
		else if (str[*i] == 'C')
			return ('C');
		else if (str[*i] == 'F')
			return ('F');
		else
			return ('X');
	}
	else if (str[*i] && !str[(*i) + 1])
		return ('X');
	return ('Q');
}

void	handle_x(char **sprites, int fd, char *str)
{
	int	i;

	write(2, "Error\nError while parsing .cub file\n", 36);
	i = 0;
	while (i < 6)
	{
		if (sprites[i])
			free(sprites[i]);
		i++;
	}
	free(sprites);
	free(str);
	close(fd);
	exit(1);
}

int	fill_texture_condition(char c, char **sprites, char *str, \
	int j)
{
	int		i;
	char	*list;
	int		count;	
	int		val;

	i = -1;
	list = "NSEWFC";
	count = 0;
	while (++i < 6)
	{
		if (c == list[i])
		{
			val = 3;
			if (c == 'F' || c == 'C')
				val--;
			if (sprites[i] == NULL && ft_strlen(str) > j + val)
				(count)++;
			if (sprites[i] == NULL && ft_strlen(str) > j + val)
				sprites[i] = ft_strdup(str + j + val);
			else
				print_texture_error(i);
			break ;
		}
	}
	return (count);
}

void	fill_textures(char *str, int *count, char **sprites, int fd)
{
	int		j;
	char	c;

	j = 0;
	c = check_char(str, &j);
	*count += fill_texture_condition(c, sprites, str, j);
	if (c == 'X')
		handle_x(sprites, fd, str);
}
