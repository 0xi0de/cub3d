/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:47:11 by lbetmall         ###   ########.fr       */
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
