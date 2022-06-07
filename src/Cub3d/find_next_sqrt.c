/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_sqrt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:33:31 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:33:55 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	find_tx(t_raycast ray, int x)
{
	if (ray.start_point.x == ray.end_point.x)
		return (-1);
	return ((double)(x - ray.start_point.x)
		/ (ray.end_point.x - ray.start_point.x));
}

double	find_ty(t_raycast ray, int y)
{
	if (ray.start_point.y == ray.end_point.y)
		return (-1);
	return ((double)(y - ray.start_point.y)
		/ (ray.end_point.y - ray.start_point.y));
}
