/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:38:48 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/01 16:04:49 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

void	fatal_error(void)
{
	if (write(2, "Fatal error\n", 12) < 0)
		exit(0);
	exit(EXIT_FAILURE);
}
