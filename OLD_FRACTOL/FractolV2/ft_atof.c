/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:56:28 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/06 16:00:02 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_atof	init_values(void)
{
	t_atof	values;

	values.a = 0.0;
	values.e = 0;
	values.c = 0;
	values.sign = 1;
	values.i = 0;
	return (values);
}

t_atof	decimal_value(const char *s, t_atof values)
{
	values.i++;
	while (s[values.i] != '\0' && ft_isdigit(s[values.i]))
	{
		values.a = values.a * 10.0 + (s[values.i] - '0');
		values.e = values.e - 1;
		values.i++;
	}
	return (values);
}

t_atof	negative_value(const char *s, t_atof values)
{
	values.sign = -1;
	values.c = 0;
	values.i++;
	if (s[values.i] == '+')
		values.i++;
	else if (s[values.i] == '-')
	{
		ft_putstr("Wrong value for julia set\n");
		exit(0);
	}
	while (ft_isdigit(s[values.i]))
	{
		values.a = values.c * 10 + (s[values.i] - '0');
		values.i++;
	}
	if (s[values.i] == '.')
		values = decimal_value(s, values);
	return (values);
}

double	atof(const char *s)
{
	t_atof	values;

	values = init_values();
	while (s[values.i] != '\0' && ft_isdigit(s[values.i]))
	{
		values.a = values.a * 10.0 + (s[values.i] - '0');
		values.i++;
	}
	if (s[values.i] == '.')
		values = decimal_value(s, values);
	if (s[values.i] == '-')
		values = negative_value(s, values);
	while (values.e > 0)
	{
		values.a *= 10.0;
		values.e--;
	}
	while (values.e < 0)
	{
		values.a *= 0.1;
		values.e++;
	}
	return (values.a * values.sign);
}
