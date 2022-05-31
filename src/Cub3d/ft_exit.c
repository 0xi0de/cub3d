/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:38:48 by tallal--          #+#    #+#             */
/*   Updated: 2022/05/31 17:26:49 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_exit(t_info *info, int value, int **tab_int, char **tab_char)
{
	if (info)
		free(info);

	if (write(2, "Error\n", 6) < 0)
		exit(1);
	exit(value);
}

void	fatal_error(void)
{
	if (write(2, "Fatal error\n", 12) < 0)
		exit(0);
	exit(EXIT_FAILURE);
}
