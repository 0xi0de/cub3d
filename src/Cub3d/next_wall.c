/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:47:25 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/01 18:15:57 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	case_one(t_info *info, int i, int *x_col, int *y_col)
{
	int		y;
	double	t;

	t = find_tx(info->raycast, info->map[i].rect.x + WALL_W);
	y = info->raycast.start_point.y + t * (info->raycast.end_point.y - \
			info->raycast.start_point.y);
	if (y >= info->map[i].rect.y && y < info->map[i].rect.y + WALL_H)
	{
		if (info->raycast.start_point.x < info->raycast.end_point.x)
		{
			*x_col = info->map[i].rect.x + WALL_W;
			*y_col = y;
			return (i + 1);
		}
	}
	return (0);
}

int	case_two(t_info *info, int i, int *x_col, int *y_col)
{
	int		x;
	double	t;

	t = find_ty(info->raycast, info->map[i].rect.y + WALL_H);
	x = info->raycast.start_point.x + t * (info->raycast.end_point.x - \
			info->raycast.start_point.x);
	if (x >= info->map[i].rect.x && x < info->map[i].rect.x + WALL_W)
	{
		if (info->raycast.start_point.y < info->raycast.end_point.y)
		{
			*x_col = x;
			*y_col = info->map[i].rect.y + WALL_H;
			return (i + info->block_w);
		}
	}
	return (0);
}

int	case_three(t_info *info, int i, int *x_col, int *y_col)
{
	int		y;
	double	t;

	t = find_tx(info->raycast, info->map[i].rect.x);
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
	return (0);
}

int	case_four(t_info *info, int i, int *x_col, int *y_col)
{
	int		x;
	double	t;

	t = find_ty(info->raycast, info->map[i].rect.y);
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
	return (0);
}

int	next_wall(t_info *info, int i, int *x_col, int *y_col)
{
	double	t;
	int		res;

	t = find_tx(info->raycast, info->map[i].rect.x + WALL_W);
	res = 0;
	if (t >= 0 && t <= 1)
		res = case_one(info, i, x_col, y_col);
	t = find_ty(info->raycast, info->map[i].rect.y + WALL_H);
	if ((t >= 0 && t <= 1) && !res)
		res = case_two(info, i, x_col, y_col);
	t = find_tx(info->raycast, info->map[i].rect.x);
	if ((t >= 0 && t <= 1) && !res)
		res = case_three(info, i, x_col, y_col);
	t = find_ty(info->raycast, info->map[i].rect.y);
	if ((t >= 0 && t <= 1) && !res)
		res = case_four(info, i, x_col, y_col);
	if (res)
		return (res);
	return (-1);
}
