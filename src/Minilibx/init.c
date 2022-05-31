/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:19 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/31 15:43:31 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include "mlx.h"

void	init_mlx(t_info_mlx	*info_mlx, int w, int h)
{
	info_mlx->mlx_ptr = mlx_init();
	info_mlx->win_ptr = mlx_new_window(info_mlx->mlx_ptr, w, h, "cub3d");
}

void	init_texture(t_info_mlx	*info_mlx, t_texture *texture, char *file)
{
	texture->img = mlx_xpm_file_to_image(info_mlx->mlx_ptr,
			file, &texture->width, &texture->height);
	if (!texture->img)
		return ;
	texture->data_img = mlx_get_data_addr(texture->img,
			&texture->bpp, &texture->size_line,
			&texture->endian);
	texture->pixel_img = (uint8_t *)texture->data_img;
}
