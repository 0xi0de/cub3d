/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealkey.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:13:20 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/01 17:18:58 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minilibx.h"
#include <stdio.h>
#include <stdlib.h>

int	button_press(t_info *info)
{
	final_free(info);
	return (0);
}

int	dealkey(int key, t_info *info)
{
	if (key == 65307)
		final_free(info);
	if (key == W_KEY)
		info->player.up = 1;
	if (key == S_KEY)
		info->player.down = 1;
	if (key == A_KEY)
		info->player.left = 1;
	if (key == D_KEY)
		info->player.right = 1;
	if (key == RR_KEY)
		info->player.r_rotation = 1;
	if (key == RL_KEY)
		info->player.l_rotation = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == W_KEY)
		info->player.up = 0;
	if (key == S_KEY)
		info->player.down = 0;
	if (key == A_KEY)
		info->player.left = 0;
	if (key == D_KEY)
		info->player.right = 0;
	if (key == RR_KEY)
		info->player.r_rotation = 0;
	if (key == RL_KEY)
		info->player.l_rotation = 0;
	return (0);
}
