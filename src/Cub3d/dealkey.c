/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealkey.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:13:20 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/02 00:40:19 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx.h"
#include <stdio.h>
#include <stdlib.h>

void	movement(t_info *info)
{
	int	speed_x;
	int	speed_y;

	speed_x = 0;
	speed_y = 0;
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
	printf("speed_y = %d\n", speed_y);
	printf("speed_x = %d\n", speed_x);
}

void	raycasting(t_info *info)
{
	info->raycast.start_point.x = info->player.element.rect.x;
	info->raycast.start_point.y = info->player.element.rect.y;
	info->raycast.end_point.x = 800;
	info->raycast.end_point.y = 800;
}

int	dealkey(int key, t_info *info)
{
	printf("I pressed [%d]\n", key);
	printf("les bools sont = %d %d %d %d\n", info->player.up, info->player.down, info->player.left, info->player.right);
	if (key == 53)
		exit(0);
	if (key == W_KEY)
		info->player.up = 1;
	if (key == S_KEY)
		info->player.down = 1;
	if (key == A_KEY)
		info->player.left = 1;
	if (key == D_KEY)
		info->player.right = 1;
	printf("les bools sont = %d %d %d %d\n", info->player.up, info->player.down, info->player.left, info->player.right);
	movement(info);
	raycasting(info);
	render_map(&info->mlx_info, info->map, 8, 8);
	render_player(&info->mlx_info, &info->player.element);
	return (0);
}

int	key_release(int key, t_info *info)
{
	(void)info;
	printf("J'ai release ta mèr... la touche [%d]\n", key);
	if (key == W_KEY)
		info->player.up = 0;
	if (key == S_KEY)
		info->player.down = 0;
	if (key == A_KEY)
		info->player.left = 0;
	if (key == D_KEY)
		info->player.right = 0;
	return (0);
}
