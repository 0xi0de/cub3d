/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:42:59 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/12 12:39:15 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	frac_type_cut(char **argv, t_info *info)
{
	if (argv[1] && !ft_strcmp(argv[1], "1") && !argv[2])
		info->mandel = 1;
	else if (argv[1] && !ft_strcmp(argv[1], "2"))
	{
		info->julia = 1;
		if (!argv[2])
		{
			info->julia_param1 = -0.25;
			info->julia_param2 = 0.66;
			ft_putstr("Default values selected for Julia: -0.25 0.66");
		}
		else if (argv[2] && argv[3] && check_str(argv + 2))
		{
			info->julia_param1 = atof(argv[2]);
			info->julia_param2 = atof(argv[3]);
		}
		else
		{
			exit(0);
		}
	}
}

void	parsing(char **argv, t_info *info)
{
	info->mandel = 0;
	info->julia = 0;
	frac_type_cut(argv, info);
	if (argv[1] && !ft_strcmp(argv[1], "1") && argv[2])
	{
		ft_putstr("\n---\n");
		ft_putstr("Error: wrong number of arguments\n");
		ft_putstr("Usage: ./frac <frac_number[1 / 2]> [julia set parameters]\n");
		ft_putstr("Example: ./frac 1  or  ./frac 2 [0.285 0.01]\n");
		ft_putstr("Options between brackets[] are not necessary");
		ft_putstr("\n---\n\n");
		exit(0);
	}
	else if (!argv[1] || (ft_strcmp(argv[1], "1") != 0
			&& ft_strcmp(argv[1], "2") != 0))
	{
		ft_putstr("\n---\n");
		ft_putstr("Error: wrong number of arguments\n");
		ft_putstr("Usage: ./frac <frac_number[1 / 2]> [julia set parameters]\n");
		ft_putstr("Example: ./frac 1  or  ./frac 2 [0.285 0.01]\n");
		ft_putstr("Options between brackets[] are not necessary");
		ft_putstr("\n---\n\n");
		exit(0);
	}
}
