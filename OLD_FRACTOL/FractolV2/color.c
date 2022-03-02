/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:22:57 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/04 14:22:59 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_color(unsigned int iter, t_info *info)
{
	return (info->color_r * iter * 0xFFFFFF / 50.0);
}
