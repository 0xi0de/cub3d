/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:21:36 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/12 11:57:51 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	generate_float(t_info *info)
{
	int						fd;
	unsigned int			nb;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("Couldn't open /dev/urandom\n");
		end_prog(info);
	}
	if (read(fd, &nb, 4) == -1)
	{
		ft_putstr("Couldn't read in /dev/urandom\n");
		end_prog(info);
	}
	if (close(fd) == -1)
	{
		ft_putstr("Couldn't close /dev/urandom\n");
		end_prog(info);
	}
	return (nb / 4294967295.0 + 0.5);
}
