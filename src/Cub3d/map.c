/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:42:51 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/07 15:43:32 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(int **map_int, int line_len)
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

void	fill_map_condition(t_info *info, int **map_int, int line_len, \
	int i)
{
	int	j;

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
}

void	fill_map(t_info *info, int **map_int, int line_len, int nb_line)
{
	int	i;

	i = 0;
	while (i < nb_line)
	{
		fill_map_condition(info, map_int, line_len, i);
		i++;
	}
	deltab((char **)map_int);
}

int	parse_map(t_info *info, char **map_txt)
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
	{
		deltab((char **)map_int);
		deltab(map_txt);
		return (-1);
	}
	fill_map(info, map_int, line_len, i);
	deltab(map_txt);
	return (0);
}

void	print_texture_error(int i)
{
	write(2, "Warning! Multiple arguments for ", 32);
	if (i == 0)
		write(2, "NO", 2);
	else if (i == 1)
		write(2, "SO", 2);
	else if (i == 2)
		write(2, "EA", 2);
	else if (i == 3)
		write(2, "WE", 2);
	else if (i == 4)
		write(2, "F", 1);
	else
		write(2, "C", 1);
	write(2, ", the first one will be selected\n", 33);
}
