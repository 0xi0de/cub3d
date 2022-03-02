/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:05:48 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/07 19:54:27 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	init_complex(double a, double b)
{
	t_complex	c;

	c.re = a;
	c.im = b;
	return (c);
}

t_complex	mult(t_complex c1, t_complex c2)
{
	t_complex	mult;

	mult.re = c1.re * c2.re - c1.im * c2.im;
	mult.im = c1.re * c2.im + c2.re * c1.im;
	return (mult);
}

t_complex	add(t_complex c1, t_complex c2)
{
	t_complex	add;

	add.re = c1.re + c2.re;
	add.im = c1.im + c2.im;
	return (add);
}

double	module(t_complex a)
{
	double	mod;

	mod = hypot(a.re, a.im);
	return (mod);
}
