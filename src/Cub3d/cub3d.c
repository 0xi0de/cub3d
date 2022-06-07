/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:05:37 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:32:22 by lbetmall         ###   ########.fr       */
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
		rot += 0.07;
	if (info->player.l_rotation)
		rot -= 0.07;
	info->player.rotation += rot;
	speed_y += info->player.up;
	speed_y -= info->player.down;
	speed_x -= info->player.left;
	speed_x += info->player.right;
	angle = atan2(speed_x, speed_y) + info->player.rotation;
	if (speed_x || speed_y)
	{
		speed_y = 7 * sin(angle);
		speed_x = 7 * cos(angle);
		info->player.pos.y += speed_y;
		info->player.pos.x += speed_x;
	}
}

int	render_next_frame(t_info *info)
{
	movement(info, 0.0, 0.0);
	raycastings(info, info->player.rotation);
	return (0);
}

int	check_file(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 4)
	{
		if (str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c'
			&& str[i - 4] == '.')
			return (1);
	}
	return (0);
}

void	write_error_msg(char *err1, char *err2)
{
	if (write(2, err1, ft_strlen(err1)) < 0)
		exit(1);
	if (write(2, err2, ft_strlen(err2)) < 0)
		exit(1);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc != 2)
	{
		write_error_msg("Error\n", "Wrong number of arguments\n");
		return (1);
	}
	if (!check_file(argv[1]))
	{
		write_error_msg("Error\n", "Invalid file type\n");
		return (1);
	}
	info = parser(argv[1]);
	if (!info)
	{
		printf("Error loading map\n");
		final_free(info);
	}
	print_map(info);
	mlx_hook(info->mlx_info.win_ptr, 2, 1L << 0, dealkey, info);
	mlx_hook(info->mlx_info.win_ptr, 3, 1L << 1, key_release, info);
	mlx_hook(info->mlx_info.win_ptr, 33, 0L, button_press, info);
	mlx_loop_hook(info->mlx_info.mlx_ptr, render_next_frame, info);
	mlx_loop(info->mlx_info.mlx_ptr);
	return (0);
}
