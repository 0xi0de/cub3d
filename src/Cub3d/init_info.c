/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:21:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/19 12:00:29 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

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

void	init_walls(t_info *info)
{
	int		i;
	t_color	wall_color;

	i = 0;
	wall_color.r = 0xC0;
	wall_color.g = 0x7A;
	wall_color.b = 0x4B;
	while (i < SCREEN_W)
	{
		init_texture(&info->mlx_info, info->wall_texture + i, 1, SCREEN_H - i);
		fill_rect(info->wall_texture + i, wall_color);
		i++;
	}
	wall_color.r = 0xFF;
	wall_color.g = 0xFF;
	wall_color.b = 0xFF;
	init_texture(&info->mlx_info, &info->wall_texture2d, WALL_W, WALL_H);
	fill_rect(&info->wall_texture2d, wall_color);
	wall_color.r = 0x0;
	wall_color.g = 0x0;
	wall_color.b = 0x0;
	init_texture(&info->mlx_info, &info->map2d, SCREEN_W, SCREEN_H);
	fill_rect(&info->map2d, wall_color);
}

void	init_floor_ceiling(t_info *info)
{
	t_color	color_floor;
	t_color	color_ceil;

	color_ceil.r = 0x3F;
	color_ceil.g = 0x30;
	color_ceil.b = 0x17;
	color_floor.r = 0x70;
	color_floor.g = 0x70;
	color_floor.b = 0x70;
	info->floor.rect.x = 0;
	info->floor.rect.y = SCREEN_H / 2;
	info->floor.rect.w = SCREEN_W;
	info->floor.rect.h = SCREEN_H / 2;
	info->ceiling.rect.x = 0;
	info->ceiling.rect.y = 0;
	info->ceiling.rect.w = SCREEN_W;
	info->ceiling.rect.h = SCREEN_H / 2;
	init_texture(&info->mlx_info, &info->ceiling.texture,
		SCREEN_W, SCREEN_H / 2);
	init_texture(&info->mlx_info, &info->floor.texture, SCREEN_W, SCREEN_H / 2);
	fill_rect(&info->floor.texture, color_floor);
	fill_rect(&info->ceiling.texture, color_ceil);
}

#include <stdio.h>

t_info	*init_info(int map_w, int map_h)
{
	t_info		*info;

	info = ft_calloc(sizeof(t_info) + sizeof(t_element) * map_w * map_h);
	if (!info)
		fatal_error();
	info->map_w = map_w;
	info->map_h = map_h;
	init_mlx(&info->mlx_info, SCREEN_W, SCREEN_H);
	init_player(info);
	info->block_h = map_h;
	info->block_w = map_w;
	init_floor_ceiling(info);
	//init_walls(info);
	init_texture(&info->mlx_info, &info->map3d, SCREEN_W, SCREEN_H);
	info->img = mlx_new_image(info->mlx_info.mlx_ptr, SCREEN_W, SCREEN_W);
	info->data_img = mlx_get_data_addr(info->img,
			&info->line.bpp, &info->line.size_line, &info->line.endian);
	info->pixel_img = (uint8_t *)info->data_img;
	return (info);
}
