/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:21:40 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/01 18:20:51 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

void	init_player(t_info *info)
{
	info->player.up = 0;
	info->player.down = 0;
	info->player.left = 0;
	info->player.right = 0;
	info->player.rotation = 0;
	info->player.l_rotation = 0;
	info->player.r_rotation = 0;
}


int	is_digit(char c)
{
	if (!((c >= '0' && c <= '9') || c == ',' || c == '\t' || c == '\n'
			|| c == '\f' || c == '\v' || c == '\r'
			|| c == ' ' || c == '\0'))
		return (0);
	return (1);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\f'
			|| c == '\v' || c == '\r' || c == ' ')
		return(1);
	return(0);
}

int	ft_atoi(char *str, t_info *info, char **sprites, int *x)
{
	long	i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] && ft_isspace(str[i]))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == ',')
		info->coma_count++;
	info->index += i + 1;
	if (res * neg < 0 || res * neg > 255 || str[0] == '\0'
		|| info->coma_count > 2 || !is_digit(str[i]))
	{
		*x = 1;
		return (-1);
	}
	return (res * neg);
}

void	init_floor_ceiling(t_info *info, char **sprites, char **map_txt)
{
	t_color	color_floor;
	t_color	color_ceil;
	int		x;
	char	*tmp;

	x = 0;
	tmp = sprites[5];
	info->color_ceil.r = ft_atoi(sprites[5] + info->index, info, sprites, &x);
	info->color_ceil.g = ft_atoi(sprites[5] + info->index, info, sprites, &x);
	info->color_ceil.b = ft_atoi(sprites[5] + info->index, info, sprites, &x);
	info->index = 0;
	info->coma_count = 0;
	free(tmp);
	sprites[5] = NULL;
	tmp = sprites[4];
	info->color_floor.r = ft_atoi(sprites[4] + info->index, info, sprites, &x);
	info->color_floor.g = ft_atoi(sprites[4] + info->index, info, sprites, &x);
	info->color_floor.b = ft_atoi(sprites[4] + info->index, info, sprites, &x);
	free(tmp);
	sprites[4] = NULL;
	if (x)
	{
		printf("Wrong value for C or F colors\n");
		x = 0;
		while (x < 6)
		{
			if (sprites[x])
				free(sprites[x]);
			x++;
		}
		deltab(map_txt);
		free(sprites);
		final_free(info);
	}
	info->floor.rect.x = 0;
	info->floor.rect.y = SCREEN_H / 2;
	info->floor.rect.w = SCREEN_W;
	info->floor.rect.h = SCREEN_H / 2;
	info->ceiling.rect.x = 0;
	info->ceiling.rect.y = 0;
	info->ceiling.rect.w = SCREEN_W;
	info->ceiling.rect.h = SCREEN_H / 2;
	fill_rect(&info->floor.texture, color_floor);
	fill_rect(&info->ceiling.texture, color_ceil);
}

t_info	*init_info(int map_w, int map_h, char **sprites, char **map_txt)
{
	int		i;
	t_info	*info;

	info = ft_calloc(sizeof(t_info) + sizeof(t_element) * map_w * map_h);
	if (!info)
		fatal_error();
	info->map_w = map_w;
	info->map_h = map_h;
	init_mlx(&info->mlx_info, SCREEN_W, SCREEN_H);
	init_player(info);
	info->block_h = map_h;
	info->block_w = map_w;
	info->index = 0;
	init_floor_ceiling(info, sprites, map_txt);
	i = 0;
	while (i < 4)
	{
		init_texture(&info->mlx_info, &info->map3d[i], sprites[i]);
		free(sprites[i]);
		sprites[i] = NULL;
		if (!info->map3d[i].img)
		{
			printf("Error loading textures\n");
			i = 0;
			while (i < 6)
			{
				if (sprites[i])
					free(sprites[i]);
				i++;
			}
			deltab(map_txt);
			free(sprites);
			final_free(info);
		}
		i++;
	}
	free(sprites);
	info->img = mlx_new_image(info->mlx_info.mlx_ptr, SCREEN_W, SCREEN_W);
	info->data_img = mlx_get_data_addr(info->img,
			&info->line.bpp, &info->line.size_line, &info->line.endian);
	info->pixel_img = (uint8_t *)info->data_img;
	return (info);
}
