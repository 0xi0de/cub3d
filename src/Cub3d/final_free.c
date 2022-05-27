/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:50:42 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/27 18:19:11 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	final_free(t_info *info)
{
	mlx_loop_end(info->mlx_info.mlx_ptr);
	mlx_destroy_window(info->mlx_info.mlx_ptr, info->mlx_info.win_ptr);
	mlx_destroy_image(info->mlx_info.mlx_ptr, info->img);
//	mlx_destroy_image(info->mlx_info.mlx_ptr, info->map3d.img_no);
	// mlx_destroy_image(info->mlx_info.mlx_ptr, info->ceiling.texture.img);
	// mlx_destroy_image(info->mlx_info.mlx_ptr, info->floor.texture.img);
	mlx_destroy_display(info->mlx_info.mlx_ptr);
	free(info->mlx_info.mlx_ptr);
	free(info);
	exit (0);
}
