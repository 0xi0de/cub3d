/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:39:11 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/01 18:16:03 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	check_wall(t_info *info, int x, int y)
{
	if (info->map[get_position(info, x, y)].is_wall)
		return (1);
	return (0);
}

int	get_position(t_info *info, int x, int y)
{
	int		res;

	res = x / WALL_W + y / WALL_H * info->map_w;
	return (res);
}
