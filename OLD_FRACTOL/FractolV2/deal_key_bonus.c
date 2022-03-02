/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:26:23 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/11 17:26:24 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	end_prog(t_info *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img_ptr);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	exit(0);
}

int	deal_key(int key, void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (key == 123)
		info->start_point.re -= 0.42 * info->amplitude;
	else if (key == 124)
		info->start_point.re += 0.42 * info->amplitude;
	else if (key == 126)
		info->start_point.im += 0.42 * info->amplitude;
	else if (key == 125)
		info->start_point.im -= 0.42 * info->amplitude;
	else if (key == 3)
	{
		if (info->funny_mode == 0)
			info->funny_mode = 1;
		else if (info->funny_mode == 1)
			info->funny_mode = 0;
	}
	if (key == 53)
		end_prog(info);
	render(info);
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}
