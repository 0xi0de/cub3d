/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:21:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:58:22 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

void	init_player(t_info *info)
{
	info->player.up = 0;
	info->player.down = 0;
	info->player.left = 0;
	info->player.right = 0;
	info->player.rotation = 0;
	info->player.l_rotation = 0;
	info->player.r_rotation = 0;
}

void	init_ceiling(t_info *info)
{
	info->block_h = info->map_h;
	info->block_w = info->map_w;
	info->ceiling.rect.x = 0;
	info->ceiling.rect.y = 0;
	info->ceiling.rect.w = SCREEN_W;
	info->ceiling.rect.h = SCREEN_H / 2;
}

void	init_floor_ceiling(t_info *info, char **sprites, char **map)
{
	t_color	color_floor;
	t_color	color_ceil;
	char	*tmp;

	tmp = sprites[5];
	info->color_ceil.r = ft_atoi(sprites[5] + info->index, info, sprites, map);
	info->color_ceil.g = ft_atoi(sprites[5] + info->index, info, sprites, map);
	info->color_ceil.b = ft_atoi(sprites[5] + info->index, info, sprites, map);
	info->index = 0;
	info->coma_count = 0;
	free(tmp);
	sprites[5] = NULL;
	tmp = sprites[4];
	info->color_floor.r = ft_atoi(sprites[4] + info->index, info, sprites, map);
	info->color_floor.g = ft_atoi(sprites[4] + info->index, info, sprites, map);
	info->color_floor.b = ft_atoi(sprites[4] + info->index, info, sprites, map);
	free(tmp);
	sprites[4] = NULL;
	info->floor.rect.x = 0;
	info->floor.rect.y = SCREEN_H / 2;
	info->floor.rect.w = SCREEN_W;
	info->floor.rect.h = SCREEN_H / 2;
	init_ceiling(info);
	fill_rect(&info->floor.texture, color_floor);
	fill_rect(&info->ceiling.texture, color_ceil);
}

void	img_check(t_info *info, char **sprites, int i, char **map)
{
	if (!info->map3d[i].img)
	{
		write(2, "Error\nError loading textures\n", 27);
		i = 0;
		while (i < 6)
		{
			if (sprites[i])
				free(sprites[i]);
			i++;
		}
		deltab(map);
		free(sprites);
		final_free(info);
	}
}

t_info	*init_info(int map_w, int map_h, char **sprites, char **map_txt)
{
	int		i;
	t_info	*info;

	info = ft_calloc(sizeof(t_info) + sizeof(t_element) * map_w * map_h);
	if (!info)
		fatal_error();
	info->map_w = map_w;
	info->map_h = map_h;
	init_mlx(&info->mlx_info, SCREEN_W, SCREEN_H);
	init_player(info);
	info->index = 0;
	init_floor_ceiling(info, sprites, map_txt);
	i = -1;
	while (++i < 4)
	{
		init_texture(&info->mlx_info, &info->map3d[i], sprites[i]);
		sprites[i] = delstr(sprites[i]);
		img_check(info, sprites, i, map_txt);
	}
	free(sprites);
	info->img = mlx_new_image(info->mlx_info.mlx_ptr, SCREEN_W, SCREEN_W);
	info->data_img = mlx_get_data_addr(info->img,
			&info->line.bpp, &info->line.size_line, &info->line.endian);
	info->pixel_img = (uint8_t *)info->data_img;
	return (info);
}
