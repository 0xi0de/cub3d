/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/01 18:35:01 by tallal--         ###   ########.fr       */
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

	i = 0;
	info->color_ceil.endian = info->line.endian;
	info->color_floor.endian = info->line.endian;
	nb_pixel = 4 * SCREEN_H * SCREEN_W;
	while (i < nb_pixel)
	{
		if (i < nb_pixel / 2)
			color_pixel(info->pixel_img + i, info->color_ceil);
		else
			color_pixel(info->pixel_img + i, info->color_floor);
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

void	handle_north_south(t_line line, t_ratio ratio, \
	t_texture texture, uint8_t *pixel_img)
{
	int	i;

	i = 0;
	line.raypoint.x = (int)line.raypoint.x % WALL_W;
	ratio.final_y = 0;
	ratio.final_x = line.raypoint.x * ratio.ratio_x;
	if (ratio.dy < 0)
	{
		ratio.final_y = ratio.ratio_y * -ratio.dy;
		ratio.dy = 0;
	}
	ratio.size = line.pos_x * 4 + ratio.dy * line.size_line;
	while (i < line.lenght)
	{
		ratio.index = ratio.size;
		if (ratio.index > 0 && ratio.index < SCREEN_H * SCREEN_W * 4)
			get_pxl(&pixel_img[ratio.index], ratio.final_x, \
			ratio.final_y, texture);
		ratio.final_y += ratio.ratio_y;
		ratio.size += line.size_line;
		i++;
	}
}

void	handle_east_west(t_line line, t_ratio ratio, \
	t_texture texture, uint8_t *pixel_img)
{
	int	i;

	i = 0;
	line.raypoint.y = (int)line.raypoint.y % WALL_H;
	ratio.final_y = 0;
	ratio.final_x = line.raypoint.y * ratio.ratio_x;
	if (ratio.dy < 0)
	{
		ratio.final_y = ratio.ratio_y * -ratio.dy;
		ratio.dy = 0;
	}
	ratio.size = line.pos_x * 4 + ratio.dy * line.size_line;
	while (i < line.lenght)
	{
		ratio.index = ratio.size;
		if (ratio.index > 0 && ratio.index < SCREEN_H * SCREEN_W * 4)
			get_pxl(&pixel_img[ratio.index], \
				ratio.final_x, ratio.final_y, texture);
		ratio.final_y += ratio.ratio_y;
		ratio.size += line.size_line;
		i++;
	}
}

void	draw_texture_line(t_texture texture, uint8_t *pixel_img, t_line line)
{
	t_ratio	ratio;

	ratio.dy = (SCREEN_H - line.lenght) / 2;
	ratio.ratio_x = (float)texture.width / (float)WALL_H;
	ratio.ratio_y = (float)texture.height / (float)line.lenght;
	if (line.lenght > SCREEN_H)
		line.lenght = SCREEN_H;
	if (line.orientation == 'N' || line.orientation == 'S')
		handle_north_south(line, ratio, texture, pixel_img);
	else
		handle_east_west(line, ratio, texture, pixel_img);
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
	else if (info->line.orientation == 'W')
		draw_texture_line(info->map3d[3], info->pixel_img, info->line);
}
