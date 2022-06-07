/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 00:47:00 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/07 15:51:56 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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
