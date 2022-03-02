/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:05:37 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/01 17:34:10 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

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
	mlx_loop(info->mlx_info.mlx_ptr);
	return (0);
}
