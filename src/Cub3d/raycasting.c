/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:18:40 by tallal--          #+#    #+#             */
/*   Updated: 2022/03/30 18:29:56 by tallal--         ###   ########.fr       */
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

	// t = L'emplacement du mur le plus proche dans la direction recherche, on va ensuite calculer l'endroit exact avec le x ou le y restant qui sera la seul valeur modulable en fonction de l'angle
	t = find_tx(info->raycast, info->map[i].rect.x + WALL_W);
	//printf("%d\n",  info->map[i].rect.x );
	//CHECK A DROITE
	if (t >= 0 && t <= 1)
	{
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
	}
	t = find_ty(info->raycast, info->map[i].rect.y + WALL_H);
	//CHECK EN BAS
	if (t >= 0 && t <= 1)
	{
		x = info->raycast.start_point.x + t * (info->raycast.end_point.x - \
			info->raycast.start_point.x);
		//printf("x1 = %d\n", x);
		//printf("rect.x = %d\n", info->map[i].rect.x);
		//printf("rect.x + WW = %d\n", info->map[i].rect.x + WALL_W);
		if (x >= info->map[i].rect.x && x < info->map[i].rect.x + WALL_W)
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
	//CHECK A GAUCHE
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
	//CHECK EN HAUT
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
			else
				printf("dans le else 4\n");
		}
		else
			printf(" info->map[i].rect.x= %d et x = %d \n",  info->map[i].rect.x, x);
	}
	t = find_ty(info->raycast, info->map[i].rect.y + WALL_H);
	//CHECK EN BAS
	if (t >= 0 && t <= 1)
	{

		x = info->raycast.start_point.x + t * (info->raycast.end_point.x - \
			info->raycast.start_point.x);
		//printf("x1 = %d\n", x);
		//printf("rect.x = %d\n", info->map[i].rect.x);
		//printf("rect.x + WW = %d\n", info->map[i].rect.x + WALL_W);
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
	return (-1);
}

int	raycasting(t_info *info, double angle, int *x, int *y)
{
	int		pos;
	t_coord	end;

	info->raycast.start_point.x = info->player.pos.x;
	info->raycast.start_point.y = info->player.pos.y;
	*x = info->raycast.start_point.x;
	*y = info->raycast.start_point.y;
	pos = get_position(info, *x, *y);
	info->raycast.end_point.x = info->raycast.start_point.x
		+ cos(angle) * RAY_DISTANCE;
	info->raycast.end_point.y = info->raycast.start_point.y
		+ sin(angle) * RAY_DISTANCE;
	while (!info->map[pos].is_wall)
	{
		pos = next_wall(info, pos, x, y);
		//printf("pos = %d\n", pos);
		if (pos == -1)
			return (0);

	}
	end.x = *x;
	end.y = *y;
	draw_line(info->raycast.start_point, end, info);
	return (1);
}

void	raycastings(t_info *info, double angle)
{
	t_color	wall_color;
	double	start_angle;
	double	angle_step;
	int		i;
	int		x;
	int		y;

	wall_color.r = 0x0;
	wall_color.g = 0x0;
	wall_color.b = 0x0;
	fill_rect(&info->map2D, wall_color);
	angle_step = FOV / (double)SCREEN_W;
	start_angle = angle - (FOV / 2);
	i = 0;
	clear_img(&info->map3D);
	while (i < SCREEN_W)
	{
		if (raycasting(info, start_angle + i * angle_step, &x, &y))
		{
			render_wall(info, x, y, i, ((i * angle_step) - FOV) / 2);
		}
		//else
		//	render_wall(info, x, y, i, ((i * angle_step) - FOV) / 2);
			//printf("angle %d\n", info->raycast.end_point.x);
			//render_wall(info, x, y, i, (i * angle_step) - FOV / 2);
		i++;
	}
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		info->map3D.img, 0, 0);
}
