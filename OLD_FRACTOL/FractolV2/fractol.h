/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 07:54:27 by lbetmall          #+#    #+#             */
/*   Updated: 2021/10/12 12:49:19 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./lib/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# define MAX_ITER 75
# define SCREEN_W 500
# define SCREEN_H 500
# define NBR_THREADS 32

typedef struct s_complex
{
	double	im;
	double	re;
}	t_complex;

typedef struct s_info
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*img;
	float		color_r;
	t_complex	start_point;
	double		amplitude;
	int			funny_mode;
	int			mandel;
	int			julia;
	double		julia_param1;
	double		julia_param2;
}	t_info;

typedef struct s_worker
{
	t_info	*info;
	int		nb_thread;
}	t_worker;

typedef struct s_atof
{
	double	a;
	int		e;
	int		c;
	int		sign;
	int		i;
	int		stop;
}	t_atof;

float		generate_float(t_info *info);
void		end_prog(t_info *info);
int			ft_color(unsigned int iter, t_info *info);
int			mouse_hook(int button, int x, int y, void *param);
int			deal_key(int key, void *param);
int			ract_conv(t_complex c);
void		fractal_calculation(t_info *info);
void		render(t_info *info);
void		init_struct(char **argv, t_info *info);
void		parsing(char **argv, t_info *info);
void		frac_type_cut(char **argv, t_info *info);
void		ft_putchar(char c);
void		ft_putstr(char *str);
double		atof(const char *s);
int			check_str(char **str);
int			ft_isdigit(char c);
t_atof		init_values(void);
t_complex	init_complex(double a, double b);
t_complex	mult(t_complex c1, t_complex c2);
t_complex	add(t_complex c1, t_complex c2);
double		module(t_complex a);
int			ft_strcmp(const char *s1, const char *s2);
void		*fractal_calculation_bonus(t_worker *worker_info);

#endif
