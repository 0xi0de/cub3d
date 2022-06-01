/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:38:03 by tallal--          #+#    #+#             */
/*   Updated: 2022/06/01 17:19:09 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d.h"
#include <stdlib.h>

void	*ft_calloc(unsigned long n)
{
	void			*ptr;
	unsigned long	i;

	i = 0;
	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	while (i < n)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
