/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:50:32 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/10 12:50:35 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	print_map(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	printf("-------\n");
	while (i < info->map_h)
	{
		j = 0;
		while (j < info->map_w)
		{
			if (info->map[i * info->map_w + j].is_wall)
				printf("X ");
			else
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}
