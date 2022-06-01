/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:50:42 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/01 15:28:50 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	final_free(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (info->map3d[i].img)
			mlx_destroy_image(info->mlx_info.mlx_ptr, info->map3d[i].img);
		i++;
	}
	mlx_loop_end(info->mlx_info.mlx_ptr);
	mlx_destroy_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr);
	if (info->img)
		mlx_destroy_image(info->mlx_info.mlx_ptr, info->img);
	mlx_destroy_display(info->mlx_info.mlx_ptr);
	free(info->mlx_info.mlx_ptr);
	free(info);
	exit (1);
}
