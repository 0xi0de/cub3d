/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:23:04 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/11 17:23:06 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	t_info	*info;
	double	old_amplitude;

	info = (t_info *)param;
	if (button == 5 || button == 4)
	{
		if (info->funny_mode)
			info->color_r = generate_float(info);
		else
			info->color_r = 1.5;
		old_amplitude = info->amplitude;
		if (button == 5)
			info->amplitude *= 0.8;
		else if (button == 4)
			info->amplitude *= 1.2;
		info->start_point = init_complex(x * (old_amplitude - info->amplitude)
				/ (double)SCREEN_W
				+ info->start_point.re, info->start_point.im + y
				* (info->amplitude - old_amplitude) / (double)SCREEN_H);
	}
	render(info);
	return (0);
}
