/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:45 by lbetmall          #+#    #+#             */
/*   Updated: 2022/04/21 15:08:09 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H

# define MINILIBX_H
# include "mlx.h"
# include "stdint.h"

# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				endian;
}	t_color;

typedef struct s_info_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}	t_info_mlx;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;


typedef struct s_texture
{
	char 	*sprite;
	int		width;
	int		height;
	void	*img;
	char	*data_img;
	uint8_t	*pixel_img;
	int		endian;
	int		bpp;
	int		size_line;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	 t_rect            rect;
}	t_texture;


typedef struct s_element
{
	t_texture	texture;
	t_rect		rect;
	int			is_wall;
}	t_element;

void	init_texture(t_info_mlx	*info_mlx, t_texture *texture, int w, int h);
void	init_mlx(t_info_mlx	*info_mlx, int w, int h);
void	fill_rect(t_texture *texture, t_color color);

#endif
