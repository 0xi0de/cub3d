/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:25:52 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/06 15:16:55 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	check_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] >= 'A' && str[i][j] <= 'Z') ||
					(str[i][j] >= 'a' && str[i][j] <= 'z'))
			{
				ft_putstr("Error: wrong type of arguments\n");
				ft_putstr("Example: ./frac 2 0.285 0.01");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
