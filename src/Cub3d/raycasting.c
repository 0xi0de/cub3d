/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:18:40 by tallal--          #+#    #+#             */
/*   Updated: 2022/05/31 18:16:11 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

// int	next_wall(t_info *info, int i, int *x_col, int *y_col)
// {
// 	double	t;
// 	int		x;
// 	int		y;

// 	t = find_tx(info->raycast, info->map[i].rect.x + WALL_W);
// 	if (t >= 0 && t <= 1)
// 	{
// 		y = info->raycast.start_point.y + t * (info->raycast.end_point.y - 
// 			info->raycast.start_point.y);
// 		if (y >= info->map[i].rect.y && y < info->map[i].rect.y + WALL_H)
// 		{
// 			if (info->raycast.start_point.x < info->raycast.end_point.x)
// 			{
// 				*x_col = info->map[i].rect.x + WALL_W;
// 				*y_col = y;
// 				return (i + 1);
// 			}
// 		}
// 	}
// 	t = find_ty(info->raycast, info->map[i].rect.y + WALL_H);
// 	if (t >= 0 && t <= 1)
// 	{
// 		x = info->raycast.start_point.x + t * (info->raycast.end_point.x - 
// 			info->raycast.start_point.x);
// 		if (x >= info->map[i].rect.x && x < info->map[i].rect.x + WALL_W)
// 		{
// 			if (info->raycast.start_point.y < info->raycast.end_point.y)
// 			{
// 				*x_col = x;
// 				*y_col = info->map[i].rect.y + WALL_H;
// 				return (i + info->block_w);
// 			}
// 		}
// 	}
// 	t = find_tx(info->raycast, info->map[i].rect.x);
// 	if (t >= 0 && t <= 1)
// 	{
// 		y = info->raycast.start_point.y + t * (info->raycast.end_point.y - 
// 			info->raycast.start_point.y);
// 		if (y >= info->map[i].rect.y && y <= info->map[i].rect.y + WALL_H)
// 		{
// 			if (info->raycast.start_point.x > info->raycast.end_point.x)
// 			{
// 				*x_col = info->map[i].rect.x;
// 				*y_col = y;
// 				return (i - 1);
// 			}
// 		}
// 	}
// 	t = find_ty(info->raycast, info->map[i].rect.y);
// 	if (t >= 0 && t <= 1)
// 	{
// 		x = info->raycast.start_point.x + t * (info->raycast.end_point.x - 
// 			info->raycast.start_point.x);
// 		if (x >= info->map[i].rect.x && x <= info->map[i].rect.x + WALL_W)
// 		{
// 			if (info->raycast.start_point.y > info->raycast.end_point.y)
// 			{
// 				*x_col = x;
// 				*y_col = info->map[i].rect.y;
// 				return (i - info->block_w);
// 			}
// 		}
// 	}
// 	return (-1);
// }

int	raycasting(t_info *info, double angle, int *x, int *y)
{
	int		pos;

	info->raycast.start_point.x = info->player.pos.x;
	info->raycast.start_point.y = info->player.pos.y;
	*x = info->raycast.start_point.x;
	*y = info->raycast.start_point.y;
	pos = get_position(info, *x, *y);
	if (pos == -1 || pos >= info->map_h * info->map_w)
		return (0);
	if (info->map[pos].is_void)
		return (0);
	info->raycast.end_point.x = info->raycast.start_point.x
		+ cos(angle) * RAY_DISTANCE;
	info->raycast.end_point.y = info->raycast.start_point.y
		+ sin(angle) * RAY_DISTANCE;
	while (!info->map[pos].is_wall)
	{
		pos = next_wall(info, pos, x, y);
		if (pos == -1)
			return (0);
	}
	return (1);
}

char	get_wall_pos(t_info *info, int x, int y)
{
	if (x % 100 == 0 && y % 100 != 0)
	{
		if (x > info->player.pos.x)
			return ('W');
		else
			return ('E');
	}
	else if (y % 100 == 0 && x % 100 != 0)
	{
		if (y > info->player.pos.y)
			return ('N');
		else
			return ('S');
	}
	else
		return ('C');
}

void	raycastings(t_info *info, double angle)
{
	double	start_angle;
	double	angle_step;
	int		i;
	int		x;
	int		y;
	int tmp;

	angle_step = FOV / (double)SCREEN_W;
	start_angle = angle - (FOV / 2);
	i = 0;
	clear_img(info);
	while (i < SCREEN_W)
	{
		if (raycasting(info, start_angle + i * angle_step, &x, &y))
		{
			info->line.pos_x = i;
			info->line.orientation = get_wall_pos(info, x, y);
			tmp = i;
			while (info->line.orientation == 'C' && tmp > 0)
			{
				tmp--;
				raycasting(info, start_angle + tmp * angle_step, &x, &y);
				info->line.orientation = get_wall_pos(info, x, y);
			}
			info->line.raypoint.x = x;
			info->line.raypoint.y = y;
			render_wall(info, x, y, FOV / 2 - i * angle_step);
		}
		i++;
	}
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		info->img, 0, 0);
}
