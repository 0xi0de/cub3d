/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:21:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/03 16:48:59 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

t_info	*init_info(int map_w, int map_h)
{
	t_info	*info;
	t_color	color;
	int		i;
	int		j;
	int		map[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
 	};

	info = malloc(sizeof(t_info) + sizeof(t_element) * map_w * map_h);
	if (!info)
		return (NULL);
	info->player.up = 0;
	info->player.down = 0;
	info->player.left = 0;
	info->player.right = 0;
	info->player.hitbox.w = 18;
	info->player.hitbox.h = 18;
	info->player.rotation = 0;
	info->player.l_rotation = 0;
	info->player.r_rotation = 0;
	info->map_w = map_w;
	info->map_h = map_h;
	init_mlx(&info->mlx_info, SCREEN_W, SCREEN_H);
	color.r = 0x8E;
	color.g = 0x8E;
	color.b = 0x8E;
	init_texture(&info->mlx_info, &info->wall_texture, WALL_W, WALL_H);
	fill_rect(&info->wall_texture, color);
	info->player.element.rect.x = 393;
	info->player.element.rect.y = 393;
	info->player.element.rect.w = 15;
	info->player.element.rect.h = 15;
	color.r = 0x7F;
	color.g = 0x00;
	color.b = 0xFF;
	init_texture(&info->mlx_info, &info->player_texture, 15, 15);
	fill_rect(&info->player_texture, color);
	info->player.element.texture = &info->player_texture;
	i = 0;
	info->block_h = map_h;
	info->block_w = map_w;
	while (i < map_h)
	{
		j = 0;
		while (j < map_w)
		{
			if (map[i][j])
			{
				info->map[i * map_w + j].is_wall = 1;
				info->map[i * map_w + j].texture = &info->wall_texture;
			}
			else
			{
				info->map[i * map_w + j].is_wall = 0;
				info->map[i * map_w + j].texture = NULL;
			}
			info->map[i * map_w + j].rect.w = WALL_W;
			info->map[i * map_w + j].rect.h = WALL_H;
			info->map[i * map_w + j].rect.x = j * WALL_W;
			info->map[i * map_w + j].rect.y = i * WALL_H;
			j++;
		}
		i++;
	}
	return (info);
}
