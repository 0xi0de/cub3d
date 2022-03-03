/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:05:37 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/03 17:31:43 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx.h"
#include <stdio.h>

void	movement(t_info *info)
{
	int		speed_x;
	int		speed_y;
	double	rot;

	speed_x = 0;
	speed_y = 0;
	rot = 0;
	if (info->player.up)
		speed_y -= 1;
	if (info->player.down)
		speed_y += 1;
	if (info->player.left)
		speed_x -= 1;
	if (info->player.right)
		speed_x += 1;
	if (speed_x && speed_y)
	{
		info->player.element.rect.y += 3 * speed_y;
		info->player.element.rect.x += 3 * speed_x;
	}
	else
	{
		info->player.element.rect.y += 5 * speed_y;
		info->player.element.rect.x += 5 * speed_x;
	}
	if (info->player.r_rotation)
		rot += 0.1;
	if (info->player.l_rotation)
		rot -= 0.1;
	info->player.rotation += rot;
}

int	render_next_frame(t_info *info)
{
	movement(info);
	get_position(info, info->player.element.rect.x,
		info->player.element.rect.y);
	render_map(&info->mlx_info, info->map, 8, 8);
	render_player(&info->mlx_info, &info->player.element);
	raycastings(info, info->player.rotation);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = init_info(8, 8);
	if (!info)
		return (0);
	// print_map(info);
	render_map(&info->mlx_info, info->map, 8, 8);
	render_player(&info->mlx_info, &info->player.element);
	mlx_hook(info->mlx_info.win_ptr, KEYPRESS, KEYPRESSMASK, dealkey, info);
	mlx_hook(info->mlx_info.win_ptr, 3, 0, key_release, info);
	mlx_loop_hook(info->mlx_info.mlx_ptr, render_next_frame, info);
	mlx_loop(info->mlx_info.mlx_ptr);
	return (0);
}
