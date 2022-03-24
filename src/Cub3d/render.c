/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/15 158:03:03 by tallal--         ###   ########.fr       */
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
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4] = 127;
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 1] = 127;
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 2] = 127;
		info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 3] = 127;
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

void color_pixel(uint8_t *pixel, t_color color)
{
	if (color.endian)
	{
		pixel[0] = color.r;
		pixel[1] = color.g;
		pixel[2] = color.b;
		pixel[3] = 0;
	}
	else
	{
		pixel[0] = color.b;
		pixel[1] = color.g;
		pixel[2] = color.r;
		pixel[3] = 0;
	}
}

void	clear_img(t_texture *texture)
{
	int		i;
	int		nb_pixel;
	t_color	color;

	i = 0;
	//remplacer par le BG
	color.r = 0x00;
	color.g = 0x00;
	color.b = 0x00;
	color.endian = texture->endian;
	nb_pixel = texture->bytes_per_pixel * texture->rect.h * texture->rect.w;
	while (i < nb_pixel)
	{
		color_pixel(texture->addr + i, color);
		i += 4;
	}
}

void	put_in_img(t_info *info, int d, int pos_x)
{
	int		i;
	uint8_t	*pixel;
	int		dy;
	t_color	color;

	i = 0;
	dy = (SCREEN_H - d) / 2;
	pixel = info->map3D.addr;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.endian = info->map3D.endian;
	while (i < d)
	{
		color_pixel(pixel + pos_x * info->map3D.bytes_per_pixel + info->map3D.line_length * (i + dy), color);
		i++;
	}
	//-->ifo.pixel[i] = ...
}

void	render_wall(t_info *info, int x, int y, int i, double angle)
{
	int			dx;
	int			dy;
	int			d;
	float		r;

	(void)dx;
	(void)dy;
	(void)x;
	(void)y;
	(void)angle;
	dx = info->player.pos.x - x;
	dy = info->player.pos.y - y;
	d = sqrt(dx * dx + dy * dy);
	d = cos(angle) * d;
	r = 50 / (float)d;
	if (r > 1)
		r = 1;
	if (d >= SCREEN_W)
	{
		//printf("%d\n", d);
		return ;
	}
	put_in_img(info, SCREEN_H * r, i);
	// mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
	// 	texture.img, i, d / 2);
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
