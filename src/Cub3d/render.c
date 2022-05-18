/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/18 18:12:43 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct timeval	t_timeval;

long	get_time_ms(void)
{
	t_timeval		time;
	unsigned long	t;

	gettimeofday(&time, NULL);
	t = time.tv_usec / 1000 + time.tv_sec * 1000;
	return (t);
}

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
	sky.r = 0x1A;
	sky.g = 0xA1;
	sky.b = 0xEA;
	sky.endian = info->line.endian;
	floor.r = 0x59;
	floor.g = 0x43;
	floor.b = 0x2A;
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

void	put_in_img(t_info *info, int d, int pos_x)
{
	int		i;
	uint8_t	*pixel;
	int		dy;
	unsigned char	*aa;
	t_color	color;

	i = 0;
	dy = (SCREEN_H - d) / 2;
	pixel = info->map3d.pixel_img;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.endian = info->map3d.endian;
	aa = pixel + pos_x * info->map3d.bytes_per_pixel * dy;
	while (i < d)
	{
		color_pixel(aa, color);
		aa += info->map3d.size_line;
		i++;
	}
}


t_color	get_pxl(int x, int y, void *img)
{
	int		endian;
	int		bpp;
	int		size_line;
	int		aa;
	char	*data;
	t_color	color;

	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	aa = x * 4 + y * size_line;
	color.endian = endian;
	if (color.endian)
	{
		color.r = data[aa];
		color.g = data[aa + 1];
		color.b = data[aa + 2];
	}
	else
	{
		color.b = data[aa];
		color.g = data[aa + 1];
		color.r = data[aa + 2];
	}
	return (color);
}

// void	draw_texture_line(t_texture texture, uint8_t *pixel_img, t_line line)
// {
// 	int		i;
// 	int		dy;
// 	float	ratio_x;
// 	float	ratio_y;
// 	int		index;
// 	t_color	color;

// 	i = -1;
// 	dy = (SCREEN_H - line.lenght) / 2;
// 	ratio_x = (float)texture.width / (float)100.0;
// 	ratio_y = (float)texture.height / (float)line.lenght;
// 	if (line.orientation == 'N' || line.orientation == 'S')
// 	{
// 		line.raypoint.x = (int)line.raypoint.x % 100;
// 		line.raypoint.y = (int)line.raypoint.y % line.lenght;

// 		while (++i < line.lenght)
// 		{
// 			color = get_pxl((int)line.raypoint.x * ratio_x, i * ratio_y,
// 					texture.img);
// 			index = (int)line.pos_x * 4 + (i + dy) * line.size_line;
// 			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
// 				color_pixel(&pixel_img[index], color);
// 		}
// 	}
// 	else
// 	{
// 		line.raypoint.x = (int)line.raypoint.x % line.lenght;
// 		line.raypoint.y = (int)line.raypoint.y % 100;
// 		while (++i < line.lenght)
// 		{
// 			color = get_pxl((int)line.raypoint.y * ratio_x, i * ratio_y,
// 					texture.img);
// 			index = (int)line.pos_x * 4 + (i + dy) * line.size_line;
// 			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
// 				color_pixel(&pixel_img[index], color);
// 		}
// 	}
// }

void	draw_texture_line(t_texture texture, uint8_t *pixel_img, t_line line)
{
	int		i;
	int		dy;
	float	ratio_x;
	float	ratio_y;
	int		index;
	t_color	color;
	long	time = 0;
	static long	 time_tot = 0;
	long	time2 = 0;
	static long	time_fct = 0;


	time = get_time_ms();
	if (time_tot > 1000)
	{
		printf("tot =%ld, fct_time = %ld\n", time_tot, time_fct);
		time_tot = 0;
		time_fct = 0;
	}

	i = -1;
	dy = (SCREEN_H - line.lenght) / 2;
	ratio_x = (float)texture.width / (float)100.0;
	ratio_y = (float)texture.height / (float)line.lenght;
	if (line.orientation == 'N' || line.orientation == 'S')
	{
		line.raypoint.x = (int)line.raypoint.x % 100;
		line.raypoint.y = (int)line.raypoint.y % line.lenght;
		float	aa = 0;
		int		bb = line.raypoint.x * ratio_x;
		float	cc = line.pos_x * 4 + dy * line.size_line;
		while (++i < line.lenght)
		{
			time2 = get_time_ms();
			color = get_pxl(bb, aa, texture.img);
			time_fct += get_time_ms() - time2;
			index = cc;
			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
				color_pixel(&pixel_img[index], color);
			aa += ratio_y;
			cc += line.size_line;
		}
	}
	else
	{
		line.raypoint.x = (int)line.raypoint.x % line.lenght;
		line.raypoint.y = (int)line.raypoint.y % 100;
		float	aa = 0;
		int		bb = line.raypoint.y * ratio_x;
		float	cc = line.pos_x * 4 + dy * line.size_line;
		while (++i < line.lenght)
		{
			color = get_pxl(bb, aa, texture.img);
			index = cc;
			if (index > 0 && index < SCREEN_H * SCREEN_W * 4)
				color_pixel(&pixel_img[index], color);
			aa += ratio_y;
			cc += line.size_line;
		}
	}
	time_tot += get_time_ms() - time;
}

void	render_wall(t_info *info, int x, int y, int i, double angle)
{
	int			dx;
	int			dy;
	int			d;
	float		r;

	dx = (int)info->player.pos.x - x;
	dy = (int)info->player.pos.y - y;
	d = sqrt(dx * dx + dy * dy);
	d = cos(angle) * d;
	r = 50 / (float)d;
	(void) i;
	info->line.lenght = SCREEN_H * r;
	draw_texture_line(info->map3d, info->pixel_img, info->line);
}
