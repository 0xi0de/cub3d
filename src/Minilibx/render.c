/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 01:10:54 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/03 17:12:15 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include <math.h>

void	render_map(t_info_mlx *info_mlx, t_element *elements, int w, int h)
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

void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	if (pixels == 0)
		return ;
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, win, pixelX, pixelY, 0xFFFFFF);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void	render_player(t_info_mlx *info_mlx, t_element *element)
{
	mlx_put_image_to_window(info_mlx->mlx_ptr, info_mlx->win_ptr,
		element->texture->img, element->rect.x, element->rect.y);
}
