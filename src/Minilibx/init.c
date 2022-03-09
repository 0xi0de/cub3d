/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:19 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/05 21:31:36 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include "mlx.h"

void	init_mlx(t_info_mlx	*info_mlx, int w, int h)
{
	info_mlx->mlx_ptr = mlx_init();
	info_mlx->win_ptr = mlx_new_window(info_mlx->mlx_ptr, w, h, "cub3d");
}

void	init_texture(t_info_mlx	*info_mlx, t_texture *texture, int w, int h)
{
	texture->img = mlx_new_image(info_mlx->mlx_ptr, w, h);
	texture->addr = (unsigned char *)mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	texture->rect.x = 0;
	texture->rect.y = 0;
	texture->rect.w = w;
	texture->rect.h = h;
}
