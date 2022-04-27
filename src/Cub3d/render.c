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

// void	draw_line(t_coord p1, t_coord p2, t_info *info)
// {
// 	int		dx;
// 	int		dy;
// 	int		sx;
// 	int		sy;
// 	int		err;
// 	int		e2;
// 	int		i;

// 	dx = abs(p2.x - p1.x);
// 	dy = abs(p2.y - p1.y);
// 	sx = p1.x < p2.x ? 1 : -1;
// 	sy = p1.y < p2.y ? 1 : -1;
// 	err = (dx > dy ? dx : -dy) / 2;
// 	i = 0;
// 	while (i <= dx || i <= dy)
// 	{
// 		// printf("%d %d\n", p1.x, p1.y);
// 		// printf("%d\n", info->map2D.line_length / 4);
// 		// printf("%d\n", p1.y * info->map2D.line_length / 4 + p1.x);
// 		 info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4] = 127;
// 		 info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 1] = 127;
// 		 info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 2] = 127;
// 		 info->map2D.addr[(p1.y * info->map2D.line_length / 4 + p1.x) * 4 + 3] = 127;
// 		e2 = err;
// 		if (e2 >-dx)
// 		{
// 			err -= dy;
// 			p1.x += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx;
// 			p1.y += sy;
// 		}
// 		i++;
// 	}
// }

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

void	clear_img(t_info *info)
{
	int		i;
	int		nb_pixel;
	t_color	 sky;
	t_color	floor;

	i = 0;
	//TODO: remplacer par le BG
	sky.r = 0x1A;
	sky.g = 0xA1;
	sky.b = 0xEA;
	sky.endian = info->line.endian;
	floor.r = 0x59;
	floor.g = 0x43;
	floor.b = 0x2A;
	floor.endian = info->line.endian;
	//nb_pixel = info->line.bpp * SCREEN_H * SCREEN_W;
	nb_pixel = 4 * SCREEN_H * SCREEN_W;
	//TODO: Voir si bpp ou 4
	while (i < nb_pixel)
	{
		if (i < nb_pixel / 2)
			color_pixel(info->pixel_img + i, sky);
		else
			color_pixel(info->pixel_img + i, floor);
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
	pixel = info->map3D.pixel_img;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.endian = info->map3D.endian;
	while (i < d)
	{
		color_pixel(pixel + pos_x * info->map3D.bytes_per_pixel + info->map3D.size_line * (i + dy), color);
		i++;
	}
	//-->ifo.pixel[i] = ...
}


t_color    get_pxl(int x, int y, void *img)
{
	int            endian;
	int            bpp;
	int            size_line;
	char        *data;
	t_color        color;

	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	color.endian = endian;
	if (color.endian)
	{
		color.r = data[x * 4 + y * size_line];
		color.g = data[(x * 4 + y * size_line) + 1];
		color.b = data[(x * 4 + y * size_line) + 2];
	}
	else
	{
		color.b = data[x * 4 + y * size_line];
		color.g = data[(x * 4 + y * size_line) + 1];
		color.r = data[(x * 4 + y * size_line) + 2];
	}
	return (color);
}

void	draw_texture_line(t_texture texture, uint8_t *pixel_img, t_line line)
{
	int		i;
	int		dy;
	float	ratio_x;
	float	ratio_y;
	int		index;
	//printf("raycast:%d  x:%d = y:%d avec lenght: %d;\n", line.pos_x, line.raypoint.x, line.raypoint.y, line.lenght);

	// line.raypoint.x = line.raypoint.x % line.lenght;
	// line.raypoint.y = line.raypoint.y % line.lenght;

	//printf("%d ; %d\n", line.raypoint.x, line.raypoint.y);
	t_color color;

	i = 0;
	dy = (SCREEN_H - line.lenght) / 2;
	// printf("%f %f\n", ratio_x, ratio_y);
	ratio_x = (float)texture.width / (float)100;
	ratio_y = (float)texture.height / (float)line.lenght;
	if (line.orientation == 'N' || line.orientation == 'S')
	{
		line.raypoint.x = line.raypoint.x % 100;
		line.raypoint.y = line.raypoint.y % line.lenght;

		while (i < line.lenght)
		{
			color = get_pxl(line.raypoint.x * ratio_x, i * ratio_y, texture.img);
			index = line.pos_x * 4 + (i + dy) * line.size_line;
			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
				color_pixel(&pixel_img[index], color);
			i++;
		}
	}
	else
	{
		line.raypoint.x = line.raypoint.x % line.lenght;
		line.raypoint.y = line.raypoint.y % 100;
		while (i < line.lenght)
		{
			color = get_pxl(line.raypoint.y * ratio_x, i * ratio_y, texture.img);
			index = line.pos_x * 4 + (i + dy) * line.size_line;
			//TODO: voir si condition est assez general (le screen_H...)
			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
				color_pixel(&pixel_img[index], color);
			// printf("%d\n", line.pos_x * 4 + (i + dy) * line.size_line);
			i++;
		}
	}
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
	// if (r > 1.62)
	// 	r = 1.62;
	//if (r > 1)
	//	r = 1;
	//printf("r=%f\n",r);
	// if (d >= SCREEN_W)
	// {
	// 	//printf("%d\n", d);
	// 	return ;
	// }
	(void) i;
	info->line.lenght = SCREEN_H * r;
			draw_texture_line(info->map3D, info->pixel_img, info->line);
	//put_in_img(info, SCREEN_H * r, i);

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
