/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:45:25 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:47:17 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pxl(uint8_t *pixel, int x, int y, t_texture texture)
{
	int		aa;

	aa = x * 4 + y * texture.size_line;
	pixel[0] = texture.data_img[aa];
	pixel[1] = texture.data_img[aa + 1];
	pixel[2] = texture.data_img[aa + 2];
	pixel[3] = 0;
}

void	handle_north_south(t_line line, t_ratio ratio, \
	t_texture texture, uint8_t *pixel_img)
{
	int	i;

	i = 0;
	line.raypoint.x = (int)line.raypoint.x % WALL_W;
	ratio.final_y = 0;
	ratio.final_x = line.raypoint.x * ratio.ratio_x;
	if (ratio.dy < 0)
	{
		ratio.final_y = ratio.ratio_y * -ratio.dy;
		ratio.dy = 0;
	}
	ratio.size = line.pos_x * 4 + ratio.dy * line.size_line;
	while (i < line.lenght)
	{
		ratio.index = ratio.size;
		if (ratio.index > 0 && ratio.index < SCREEN_H * SCREEN_W * 4)
			get_pxl(&pixel_img[ratio.index], ratio.final_x, \
			ratio.final_y, texture);
		ratio.final_y += ratio.ratio_y;
		ratio.size += line.size_line;
		i++;
	}
}

void	handle_east_west(t_line line, t_ratio ratio, \
	t_texture texture, uint8_t *pixel_img)
{
	int	i;

	i = 0;
	line.raypoint.y = (int)line.raypoint.y % WALL_H;
	ratio.final_y = 0;
	ratio.final_x = line.raypoint.y * ratio.ratio_x;
	if (ratio.dy < 0)
	{
		ratio.final_y = ratio.ratio_y * -ratio.dy;
		ratio.dy = 0;
	}
	ratio.size = line.pos_x * 4 + ratio.dy * line.size_line;
	while (i < line.lenght)
	{
		ratio.index = ratio.size;
		if (ratio.index > 0 && ratio.index < SCREEN_H * SCREEN_W * 4)
			get_pxl(&pixel_img[ratio.index], \
				ratio.final_x, ratio.final_y, texture);
		ratio.final_y += ratio.ratio_y;
		ratio.size += line.size_line;
		i++;
	}
}
