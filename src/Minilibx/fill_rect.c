/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:46:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/27 18:28:02 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void	one_way(unsigned char *pixel, t_color color)
{
	pixel[0] = 0;
	pixel[1] = color.r;
	pixel[2] = color.g;
	pixel[3] = color.b;
}

void	other_way(unsigned char *pixel, t_color color)
{
	pixel[0] = color.b;
	pixel[1] = color.g;
	pixel[2] = color.r;
	pixel[3] = 0;
}

void	fill_rect(t_texture *texture, t_color color)
{
	int				i;
	int				j;
	unsigned char	*pixel;

	i = 0;
	while (i < texture->rect.h)
	{
	j = 0;
		while (j < texture->rect.w)
		{
			pixel = (unsigned char *)texture->data_img
				+ (i * texture->size_line + j * (texture->bits_per_pixel / 8));
			if (texture->endian)
				one_way(pixel, color);
			else
				other_way(pixel, color);
			j++;
		}
		i++;
	}
}
