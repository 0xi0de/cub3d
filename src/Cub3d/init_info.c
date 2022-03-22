/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:21:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/22 18:15:33 by tallal--         ###   ########.fr       */
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
	int	i;
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
	init_texture(&info->mlx_info, &info->wall_texture2D, WALL_W, WALL_H);
	fill_rect(&info->wall_texture2D, wall_color);
	wall_color.r = 0x0;
	wall_color.g = 0x0;
	wall_color.b = 0x0;
	init_texture(&info->mlx_info, &info->map2D, SCREEN_W, SCREEN_H);
	fill_rect(&info->map2D, wall_color);
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

t_info	*init_info(int map_w, int map_h)
{
	t_info		*info;

	info = ft_calloc(sizeof(t_info) + sizeof(t_element) * map_w * map_h);
	if (!info)
		fatal_error();
	info->map_w = map_w;
	info->map_h = map_h;
	init_mlx(&info->mlx_info, SCREEN_W * 2, SCREEN_H);
	init_player(info);
	info->block_h = map_h;
	info->block_w = map_w;
	init_floor_ceiling(info);
	init_walls(info);
	init_texture(&info->mlx_info, &info->map3D, SCREEN_W, SCREEN_H);
	return (info);
}

	// while (i < map_h)
	// {
	// 	j = 0;
	// 	while (j < map_w)
	// 	{
	// 		if (map[i][j])
	// 		{
	// 			info->map[i * map_w + j].is_wall = 1;
	// 			info->map[i * map_w + j].texture = &info->wall_texture;
	// 		}
	// 		else
	// 		{
	// 			info->map[i * map_w + j].is_wall = 0;
	// 			info->map[i * map_w + j].texture = NULL;
	// 		}
	// 		info->map[i * map_w + j].rect.w = WALL_W;
	// 		info->map[i * map_w + j].rect.h = WALL_H;
	// 		info->map[i * map_w + j].rect.x = j * WALL_W;
	// 		info->map[i * map_w + j].rect.y = i * WALL_H;
	// 		j++;
	// 	}
	// 	i++;
	// }
