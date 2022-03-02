/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/01 01:42:00 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void    render_map(t_info_mlx *info_mlx, t_element *elements, int w, int h)
{
	int			i;
	int			j;
	t_element	*element;

	i = 0;
	mlx_clear_window(info_mlx->mlx_ptr, info_mlx->win_ptr);
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			element = elements + i * w + j;
			if (element->is_wall)
				mlx_put_image_to_window(info_mlx->mlx_ptr, info_mlx->win_ptr,
					element->texture->img, element->rect.x, element->rect.y);
			j++;
		}
		i++;
	}
}

void	render_player(t_info_mlx *info_mlx, t_element *element)
{
	mlx_put_image_to_window(info_mlx->mlx_ptr, info_mlx->win_ptr,
		element->texture->img, element->rect.x, element->rect.y);
}