/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:45 by lbetmall          #+#    #+#             */
/*   Updated: 2022/05/26 13:30:54 by lbetmall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H

# define MINILIBX_H
# include "mlx.h"
# include "stdint.h"

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100

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
	char	*north_sprite;
	char	*south_sprite;
	char	*east_sprite;
	char	*west_sprite;
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
	t_rect	rect;
}	t_texture;

typedef struct s_element
{
	t_texture	texture;
	t_rect		rect;
	int			is_wall;
	int			is_void;
}	t_element;

void	init_texture(t_info_mlx	*info_mlx, t_texture *texture, int w, int h);
void	init_mlx(t_info_mlx	*info_mlx, int w, int h);
void	fill_rect(t_texture *texture, t_color color);

#endif
