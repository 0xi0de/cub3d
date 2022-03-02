/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:27:34 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/12 12:43:24 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

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

void	*fractal_calculation_bonus(t_worker *worker_info)
{
	unsigned int	x;
	double			w;
	double			h;
	t_complex		p;
	t_info			*info;

	info = worker_info->info;
	w = info->amplitude / (double)(SCREEN_W - 1);
	h = info->amplitude / (double)(SCREEN_H - 1);
	x = worker_info->nb_thread;
	while (x < SCREEN_H * SCREEN_W)
	{
		p = init_complex((x % SCREEN_W) * info->amplitude
				/ (double)(SCREEN_W - 1)
				+ info->start_point.re, (info->start_point.im)
				- (x / SCREEN_H) * info->amplitude
				/ (double)(SCREEN_H - 1));
		info->img[x] = ft_color(fract_conv(p, info), info);
		x += NBR_THREADS;
	}
	return (NULL);
}

void	render(t_info *info)
{
	pthread_t	threads[NBR_THREADS];
	t_worker	worker_info[NBR_THREADS];
	int			i;

	i = 0;
	while (i < NBR_THREADS)
	{
		worker_info[i] = (t_worker){
			.info = info,
			.nb_thread = i
		};
		pthread_create(threads + i, NULL, (void *)fractal_calculation_bonus,
			worker_info + i);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
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
		ft_putstr("Usage: ./frac_bonus <frac_number> [julia set parameters]\n");
		ft_putstr("Example: ./frac_bonus 1  or  ./frac_bonus 2 [0.285 0.01]\n");
		ft_putstr("Options between brackets[] are not necessary");
		ft_putstr("\n---\n\n");
		return (0);
	}
	if (ft_strcmp(argv[0], "./frac_bonus") != 0)
		return (0);
	init_struct(argv, &info);
	render(&info);
	mlx_key_hook(info.win_ptr, deal_key, &info);
	mlx_mouse_hook(info.win_ptr, mouse_hook, &info);
	mlx_loop(info.mlx_ptr);
}
