/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:47:00 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/07 15:36:07 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	put_player(t_info *info, int i, int j, char c)
{
	info->player.spawn_x = j;
	info->player.spawn_y = i;
	info->player.pos.x = j * WALL_W + WALL_W / 2;
	info->player.pos.y = i * WALL_H + WALL_H / 2;
	if (c == 'S')
		info->player.rotation = PI / 2;
	else if (c == 'N')
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
		j = -1;
		while (++j < line_len)
		{
			if (j < ft_strlen(map_txt[i]))
				map_int[i][j] = map_char_to_int(map_txt[i][j]);
			else
				map_int[i][j] = 2;
		}
		i++;
	}
	map_int[i] = NULL;
	return (map_int);
}

int	valid_zero(int **map_int, int i, int j, int line_len)
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

char	**init_sprites(char **sprites)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		sprites[i] = NULL;
		i++;
	}
	return (sprites);
}

int	check_arg_map(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '1')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	parser_cut_2(t_parser *parser)
{
	if (parser->line && check_arg_map(parser->line))
	{
		fill_textures(parser->line, &parser->count, \
			parser->sprites, parser->fd);
		free(parser->line);
		while (get_next_line(parser->fd, &parser->line) > 0 \
			&& check_arg_map(parser->line))
		{
			fill_textures(parser->line, &parser->count, \
				parser->sprites, parser->fd);
			free(parser->line);
		}
	}
	if (parser->line && check_arg_map(parser->line))
		parser->map_txt = tabjoin(parser->map_txt, parser->line);
	else
		free(parser->line);
	while (get_next_line(parser->fd, &parser->line) > 0)
		parser->map_txt = tabjoin(parser->map_txt, parser->line);
	close(parser->fd);
	if (parser->line && parser->line[0])
		parser->map_txt = tabjoin(parser->map_txt, parser->line);
	else
		free(parser->line);
}

void	parser_cut(t_parser *parser)
{
	int	i;

	while (get_next_line(parser->fd, &parser->line) > 0 && parser->count < 6)
	{
		fill_textures(parser->line, &parser->count, \
			parser->sprites, parser->fd);
		free(parser->line);
	}
	parser_cut_2(parser);
	if (!parser->map_txt)
	{
		i = 0;
		while (i < 6)
		{
			if (parser->sprites[i])
				free(parser->sprites[i]);
			i++;
		}
		free(parser->sprites);
		write(2, "Error\nError loading map\n", 24);
		exit(1);
	}
}

t_info	*parser_cut_3(t_parser *parser)
{
	t_info		*info;

	info = create_info(parser->map_txt, parser->sprites);
	if (!player_spawn(info, parser->map_txt))
	{
		write(2, "Error\nError loading player location\n", 36);
		parser->map_txt = deltab(parser->map_txt);
		final_free(info);
	}
	if (parse_map(info, parser->map_txt) < 0)
	{
		write(2, "Error\nError loading map\n", 24);
		final_free(info);
	}
	return (info);
}

t_info	*parser(char *file)
{
	t_parser	parser;

	parser.map_txt = NULL;
	parser.sprites = malloc(sizeof(char *) * 6);
	if (!parser.sprites)
		exit(1);
	parser.sprites = init_sprites(parser.sprites);
	parser.fd = open(file, O_RDONLY);
	parser.count = 0;
	if (parser.fd == -1)
	{
		write(2, "Error\n", 6);
		perror("");
		free(parser.sprites);
		exit(1);
	}
	parser_cut(&parser);
	return (parser_cut_3(&parser));
}
