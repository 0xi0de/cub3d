/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/10 18:22:03 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	draw_line(t_coord p1, t_coord p2, t_info *info)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		i;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	sx = p1.x < p2.x ? 1 : -1;
	sy = p1.y < p2.y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	i = 0;
	while (i <= dx || i <= dy)
	{
		// printf("%d %d\n", p1.x, p1.y);
		// printf("%d\n", info->map2D.line_length / 4);
		// printf("%d\n", p1.y * info->map2D.line_length / 4 + p1.x);
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4] = 255;
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 1] = 255;
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 2] = 255;
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 3] = 255;
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy;
			p1.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			p1.y += sy;
		}
		i++;
	}
}

void	render_map(t_info *info)
{
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		info->floor.texture.img, info->floor.rect.x, info->floor.rect.y);
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		info->ceiling.texture.img, info->ceiling.rect.x, info->ceiling.rect.y);
}

void	render_wall(t_info *info, int x, int y, int i, double angle)
{
	int			dx;
	int			dy;
	int			d;
	t_texture	texture;

	(void)dx;
	(void)dy;
	(void)x;
	(void)y;
	dx = pow(info->player.pos.x - x, 2);
	dy = pow(info->player.pos.y - y, 2);
	printf("%f %f\n", cos(angle), sin(angle));
	//d = sqrt(dx + dy) * fabs(cos(angle));
	d = sqrt(dx + dy) * fabs(cos(angle)) / RAY_DISTANCE;
	//d = abs(info->player.pos.y - y);
	if (d >= SCREEN_W)
	{
		printf("%d\n", d);
		return ;
	}
	texture = info->wall_texture[d];
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		texture.img, i, d / 2);
}

void	render_2D_map(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		info->map2D.img, SCREEN_W, 0);
	while (y < info->map_h)
	{
		x = 0;
		while (x < info->map_w)
		{
			if (info->map[y * info->map_w + x].is_wall)
			{
				mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
					info->wall_texture2D.img, SCREEN_W + x * WALL_W, y * WALL_H);
			}
			x++;
		}
		y++;
	}
}
