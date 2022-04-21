/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:05:37 by lbetmall          #+#    #+#             */
/*   Updated: 2022/04/21 14:18:43 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// void __attribute__((destructor)) calledLast();

void	movement(t_info *info)
{
	int		speed_x;
	int		speed_y;
	double	rot;
	double	angle;

	speed_x = 0;
	speed_y = 0;
	rot = 0;
	angle = 0;
	if (info->player.r_rotation)
		rot += 0.1;
	if (info->player.l_rotation)
		rot -= 0.1;
	info->player.rotation += rot;
	speed_y += info->player.up;
	speed_y -= info->player.down;
	speed_x -= info->player.left;
	speed_x += info->player.right;
	angle = atan2(speed_x, speed_y) + info->player.rotation;
	// printf("%f\n", angle * 180 / PI);
	// printf("%f\n", cos(angle));
	if (speed_x || speed_y)
	{
		speed_y = 5 * sin(angle);
		speed_x = 5 * cos(angle);
		info->player.pos.y += speed_y;
		info->player.pos.x += speed_x;
		//printf("%d %d\n", info->player.pos.x, info->player.pos.y);
	}
}

int	render_next_frame(t_info *info)
{
	movement(info);
	//render_map(&info->mlx_info, info->map, 8, 8);
	//clear window
	mlx_clear_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr);
	render_map(info);
	//render_2D_map(info);
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
	render_map(info);
	mlx_hook(info->mlx_info.win_ptr, KEYPRESS, KEYPRESSMASK, dealkey, info);
	mlx_hook(info->mlx_info.win_ptr, 3, 0, key_release, info);
	mlx_loop_hook(info->mlx_info.mlx_ptr, render_next_frame, info);
	mlx_loop(info->mlx_info.mlx_ptr);
	return (0);
}

// void calledLast()
// {
//   printf("I am called last\n");
//   while (1);
// }
