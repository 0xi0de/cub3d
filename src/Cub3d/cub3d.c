/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:05:37 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/17 16:45:16 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void	movement(t_info *info, double speed_x, double speed_y)
{
	double	rot;
	double	angle;

	rot = 0;
	angle = 0;
	if (info->player.r_rotation)
		rot += 0.05;
	if (info->player.l_rotation)
		rot -= 0.05;
	info->player.rotation += rot;
	speed_y += info->player.up;
	speed_y -= info->player.down;
	speed_x -= info->player.left;
	speed_x += info->player.right;
	angle = atan2(speed_x, speed_y) + info->player.rotation;
	if (speed_x || speed_y)
	{
		speed_y = 3 * sin(angle);
		speed_x = 3 * cos(angle);
		info->player.pos.y += speed_y;
		info->player.pos.x += speed_x;
	}
}

int	render_next_frame(t_info *info)
{
	movement(info, 0.0, 0.0);
	mlx_clear_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr);
	//render_map(info);
	raycastings(info, info->player.rotation);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = parser(argv[1]);
	if (!info)
		return (1);
	print_map(info);
	//mlx_hook(info->mlx_info.win_ptr, 2, 1L << 0, button_press, info);
	mlx_hook(info->mlx_info.win_ptr, 2, 1L << 0, dealkey, info);
	mlx_hook(info->mlx_info.win_ptr, 3, 1L << 1, key_release, info);
	mlx_loop_hook(info->mlx_info.mlx_ptr, render_next_frame, info);
	mlx_loop(info->mlx_info.mlx_ptr);
	return (0);
}
