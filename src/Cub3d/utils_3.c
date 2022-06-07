/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:15:39 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 14:19:44 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

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
		return (1);
	return (0);
}

void	value_error(int i, t_info *info, char **sprites, char **map_txt)
{
	write(2, "Error\nWrong value for C or F colors\n", 36);
	i = 0;
	while (i < 6)
	{
		if (sprites[i])
			free(sprites[i]);
		i++;
	}
	free(sprites);
	deltab(map_txt);
	final_free(info);
}

int	neg_check(char c, long int *i)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			return (-1);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str, t_info *info, char **sprites, char **map_txt)
{
	long	i;
	int		neg;
	long	res;

	i = 0;
	res = 0;
	if (!str)
		value_error(i, info, sprites, map_txt);
	while (str[i] && ft_isspace(str[i]))
			i++;
	neg = neg_check(str[i], &i);
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
		value_error(i, info, sprites, map_txt);
	return (res * neg);
}
