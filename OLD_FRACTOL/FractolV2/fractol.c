/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 07:53:57 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/07 19:56:46 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fract_conv(t_complex c, t_info *info)
{
	unsigned int	n;
	t_complex		p;

	n = 0;
	if (info->julia)
	{
		p = c;
		c = init_complex(info->julia_param1, info->julia_param2);
	}
	else
		p = init_complex(0, 0);
	while (n < MAX_ITER && module(p) <= 2.0)
	{
		p = add(mult(p, p), c);
		n++;
	}
	return (n);
}

void	fractal_calculation(t_info *info)
{
	unsigned int	x;
	double			w;
	double			h;
	t_complex		p;

	w = info->amplitude / (double)(SCREEN_W - 1);
	h = info->amplitude / (double)(SCREEN_H - 1);
	x = 0;
	while (x < SCREEN_H * SCREEN_W)
	{
		p = init_complex((x % SCREEN_W) * info->amplitude
				/ (double)(SCREEN_W - 1)
				+ info->start_point.re, (info->start_point.im)
				- (x / SCREEN_W) * info->amplitude
				/ (double)(SCREEN_H - 1));
		info->img[x] = ft_color(fract_conv(p, info), info);
		x += 1;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
}

void	init_struct(char **argv, t_info *info)
{
	int		i;

	i = 5;
	parsing(argv, info);
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, SCREEN_W, SCREEN_H, "fract");
	info->img_ptr = mlx_new_image(info->mlx_ptr, SCREEN_W, SCREEN_H);
	info->img = (int *)mlx_get_data_addr(info->img_ptr, &i, &i, &i);
	info->start_point = init_complex(-2.0, 2.0);
	info->amplitude = 4;
	info->funny_mode = 0;
	info->color_r = 1.5;
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc > 4 || argc == 3)
	{
		ft_putstr("\n---\n");
		ft_putstr("Error: wrong number of arguments\n");
		ft_putstr("Usage: ./frac <frac_number[1 / 2]> [julia set parameters]\n");
		ft_putstr("Example: ./frac 1  or  ./frac 2 [0.285 0.01]\n");
		ft_putstr("Options between brackets[] are not necessary");
		ft_putstr("\n---\n\n");
		return (0);
	}
	if (ft_strcmp(argv[0], "./frac") != 0)
		return (0);
	init_struct(argv, &info);
	fractal_calculation(&info);
	mlx_key_hook(info.win_ptr, deal_key, &info);
	mlx_mouse_hook(info.win_ptr, mouse_hook, &info);
	mlx_loop(info.mlx_ptr);
}
