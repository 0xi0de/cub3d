/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/31 18:20:21 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	color_pixel(uint8_t *pixel, t_color color)
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
	t_color	sky;
	t_color	floor;

	i = 0;
	sky.r = 0xFF;
	sky.g = 0xFF;
	sky.b = 0xFF;
	sky.endian = info->line.endian;
	floor.r = 0x16;
	floor.g = 0x16;
	floor.b = 0x16;
	floor.endian = info->line.endian;
	nb_pixel = 4 * SCREEN_H * SCREEN_W;
	while (i < nb_pixel)
	{
		if (i < nb_pixel / 2)
			color_pixel(info->pixel_img + i, sky);
		else
			color_pixel(info->pixel_img + i, floor);
		i += 4;
	}
}

// void	put_in_img(t_info *info, int d, int pos_x)
// {
// 	int				i;
// 	uint8_t			**pixels;
// 	int				dy;
// 	unsigned char	**aa;
// 	t_color			color;

// 	i = 0;
// 	pixels = malloc(sizeof(uint8_t *) * 4);
// 	aa = malloc(sizeof(unsigned char *) * 4);
// 	dy = (SCREEN_H - d) / 2;
// 	pixels[0] = info->map3d.pixel_img_no;
// 	pixels[1] = info->map3d.pixel_img_so;
// 	pixels[2] = info->map3d.pixel_img_ea;
// 	pixels[3] = info->map3d.pixel_img_we;
// 	color.r = 0xFF;
// 	color.g = 0xFF;
// 	color.b = 0xFF;
// 	color.endian = info->map3d.endian;
// 	aa[0] = pixels[0] + pos_x * info->map3d.bytes_per_pixel * dy;
// 	aa[1] = pixels[1] + pos_x * info->map3d.bytes_per_pixel * dy;
// 	aa[2] = pixels[2] + pos_x * info->map3d.bytes_per_pixel * dy;
// 	aa[3] = pixels[3] + pos_x * info->map3d.bytes_per_pixel * dy;
// 	while (i < d)
// 	{
// 		color_pixel(aa[0], color);
// 		color_pixel(aa[1], color);
// 		color_pixel(aa[2], color);
// 		color_pixel(aa[3], color);
// 		aa[0] += info->map3d.size_line;
// 		aa[1] += info->map3d.size_line;
// 		aa[2] += info->map3d.size_line;
// 		aa[3] += info->map3d.size_line;
// 		i++;
// 	}
// }

void	get_pxl(uint8_t *pixel, int x, int y, t_texture texture)
{
	int		aa;

	aa = x * 4 + y * texture.size_line;
	pixel[0] = texture.data_img[aa];
	pixel[1] = texture.data_img[aa + 1];
	pixel[2] = texture.data_img[aa + 2];
	pixel[3] = 0;
}

void	draw_texture_line(t_texture texture, uint8_t *pixel_img, t_line line)
{
	int		i;
	int		dy;
	float	ratio_x;
	float	ratio_y;
	float	aa;
	float	cc;
	int		bb;
	int		index;

	i = -1;
	dy = (SCREEN_H - line.lenght) / 2;
	ratio_x = (float)texture.width / (float)WALL_H;
	ratio_y = (float)texture.height / (float)line.lenght;
	if (line.lenght > SCREEN_H)
		line.lenght = SCREEN_H;
	if (line.orientation == 'N' || line.orientation == 'S')
	{
		line.raypoint.x = (int)line.raypoint.x % WALL_W;
		aa = 0;
		bb = line.raypoint.x * ratio_x;
		if (dy < 0)
		{
			aa = ratio_y * -dy;
			dy = 0;
		}
		cc = line.pos_x * 4 + dy * line.size_line;
		while (++i < line.lenght)
		{
			index = cc;
			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
				get_pxl(&pixel_img[index], bb, aa, texture);
			aa += ratio_y;
			cc += line.size_line;
		}
	}
	else
	{
		line.raypoint.y = (int)line.raypoint.y % WALL_H;
		aa = 0;
		bb = line.raypoint.y * ratio_x;
		if (dy < 0)
		{
			aa = ratio_y * -dy;
			dy = 0;
		}
		cc = line.pos_x * 4 + dy * line.size_line;
		while (++i < line.lenght)
		{
			index = cc;
			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
				get_pxl(&pixel_img[index], bb, aa, texture);
			aa += ratio_y;
			cc += line.size_line;
		}
	}
}

void	render_wall(t_info *info, int x, int y, double angle)
{
	int			dx;
	int			dy;
	float		d;
	float		r;

	dx = (int)info->player.pos.x - x;
	dy = (int)info->player.pos.y - y;
	d = sqrt(dx * dx + dy * dy);
	d = cos(angle) * d;
	r = (WALL_H / 0.41421356237 / 2.0) / (float)d;
	info->line.lenght = SCREEN_H * r;
	if (info->line.orientation == 'N')
		draw_texture_line(info->map3d[0], info->pixel_img, info->line);
	else if (info->line.orientation == 'S')
		draw_texture_line(info->map3d[1], info->pixel_img, info->line);
	else if (info->line.orientation == 'E')
		draw_texture_line(info->map3d[2], info->pixel_img, info->line);
	else
		draw_texture_line(info->map3d[3], info->pixel_img, info->line);
}
