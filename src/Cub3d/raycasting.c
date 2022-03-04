/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:18:40 by tallal--          #+#    #+#             */
/*   Updated: 2022/03/03 23:15:55 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>

double	find_tx(t_raycast ray, int x)
{
	if (ray.start_point.x == ray.end_point.x)
		return (-1);
	return ((double)(x - ray.start_point.x)
		/ (ray.end_point.x - ray.start_point.x));
}

double	find_ty(t_raycast ray, int y)
{
	if (ray.start_point.y == ray.end_point.y)
		return (-1);
	return ((double)(y - ray.start_point.y)
		/ (ray.end_point.y - ray.start_point.y));
}

int	next_wall(t_info *info, int i, int *x_col, int *y_col)
{
	double	t;
	int		x;
	int		y;

	t = find_tx(info->raycast, info->map[i].rect.x + WALL_W);
	if (t >= 0 && t <= 1)
	{
		y = info->raycast.start_point.y + t * (info->raycast.end_point.y - \
			info->raycast.start_point.y);
		if (y >= info->map[i].rect.y && y <= info->map[i].rect.y + WALL_H)
		{
			if (info->raycast.start_point.x < info->raycast.end_point.x)
			{
				*x_col = info->map[i].rect.x + WALL_W;
				*y_col = y;
				return (i + 1);
			}
		}
	}
	t = find_ty(info->raycast,  info->map[i].rect.y + WALL_H);
	if (t >= 0 && t <= 1)
	{
		x = info->raycast.start_point.x + t * (info->raycast.end_point.x - \
			info->raycast.start_point.x);
		if (x >= info->map[i].rect.x && x <= info->map[i].rect.x + WALL_W)
		{
			if (info->raycast.start_point.y < info->raycast.end_point.y)
			{
				*x_col = x;
				*y_col = info->map[i].rect.y + WALL_H;
				return (i + info->block_w);
			}
		}
	}
	t = find_tx(info->raycast, info->map[i].rect.x);
	if (t >= 0 && t <= 1)
	{
		y = info->raycast.start_point.y + t * (info->raycast.end_point.y - \
			info->raycast.start_point.y);
		if (y >= info->map[i].rect.y && y <= info->map[i].rect.y + WALL_H)
		{
			if (info->raycast.start_point.x > info->raycast.end_point.x)
			{
				*x_col = info->map[i].rect.x;
				*y_col = y;
				return (i - 1);
			}
		}
	}
	t = find_ty(info->raycast, info->map[i].rect.y);
	if (t >= 0 && t <= 1)
	{
		x = info->raycast.start_point.x + t * (info->raycast.end_point.x - \
			info->raycast.start_point.x);
		if (x >= info->map[i].rect.x && x <= info->map[i].rect.x + WALL_W)
		{
			if (info->raycast.start_point.y > info->raycast.end_point.y)
			{
				*x_col = x;
				*y_col = info->map[i].rect.y;
				return (i - info->block_w);
			}
		}
	}
	return (-1);
}

void	raycasting(t_info *info, double angle)
{
	int	pos;
	int	x;
	int	y;

	(void)angle;
	info->raycast.start_point.x = info->player.element.rect.x + 7;
	info->raycast.start_point.y = info->player.element.rect.y + 7;
	x = info->raycast.start_point.x;
	y = info->raycast.start_point.y;
	pos = get_position(info, x, y);
	info->raycast.end_point.x = info->raycast.start_point.x + cos(angle) * SCREEN_W;
	info->raycast.end_point.y = info->raycast.start_point.y + sin(angle) * SCREEN_H;
	while (!info->map[pos].is_wall)
	{
		pos = next_wall(info, pos, &x, &y);
		if (pos == -1)
			break ;
	}
	if (pos != -1)
	{
		draw_line(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr, x, y, info->raycast.start_point.x, info->raycast.start_point.y);
		//printf("%d %d\n", x, y);
	}
}

void	raycastings(t_info *info, double angle)
{
	double	start_angle;
	double	end_angle;
	double	angle_step;

	angle_step = FOV / (double)200;
	start_angle = angle - (FOV / 2);
	end_angle = angle + (FOV / 2);
	while (start_angle < end_angle)
	{
		raycasting(info, start_angle);
		start_angle += angle_step;
	}
}
