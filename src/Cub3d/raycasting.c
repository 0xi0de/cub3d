/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:18:40 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/07 15:25:23 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int	raycasting(t_info *info, double angle, int *x, int *y)
{
	int		pos;

	info->raycast.start_point.x = info->player.pos.x;
	info->raycast.start_point.y = info->player.pos.y;
	*x = info->raycast.start_point.x;
	*y = info->raycast.start_point.y;
	pos = get_position(info, *x, *y);
	if (pos < 0 || pos >= info->map_h * info->map_w)
		return (0);
	//printf("pos = %d\n", pos);
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

void	handle_raycast(t_info *info, t_coord raypoint, \
	double start_angle, double angle_step)
{
	int		tmp;

	info->line.orientation = get_wall_pos(info, \
		raypoint.xi, raypoint.yi);
	tmp = info->line.pos_x;
	while (info->line.orientation == 'C' && tmp > 0)
	{
		tmp--;
		raycasting(info, start_angle + tmp * angle_step, \
			&raypoint.xi, &raypoint.yi);
		info->line.orientation = get_wall_pos(info, \
			raypoint.xi, raypoint.yi);
	}
	info->line.raypoint.x = raypoint.xi;
	info->line.raypoint.y = raypoint.yi;
	render_wall(info, raypoint.xi, raypoint.yi, \
		FOV / 2 - info->line.pos_x * angle_step);
}

void	raycastings(t_info *info, double angle)
{
	double	start_angle;
	double	angle_step;
	int		i;
	t_coord	raypoint;

	angle_step = FOV / (double)SCREEN_W;
	start_angle = angle - (FOV / 2);
	i = 0;
	clear_img(info);
	while (i < SCREEN_W)
	{
		if (raycasting(info, start_angle + i * angle_step, \
			&raypoint.xi, &raypoint.yi))
		{
			info->line.pos_x = i;
			handle_raycast(info, raypoint, start_angle, angle_step);
		}
		i++;
	}
	mlx_put_image_to_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr,
		info->img, 0, 0);
}
