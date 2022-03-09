/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:46:57 by tallal--          #+#    #+#             */
/*   Updated: 2022/02/10 18:30:29 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	free_str(char *str)
{
	if (str)
		free(str);
}

char	*delstr(char *str)
{
	free_str(str);
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
				tab[i] = delstr(tab[i]);
			i++;
		}
		free(tab);
	}
}

char	**deltab(char **str)
{
	free_tab(str);
	return (NULL);
}
