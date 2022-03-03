/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:45 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/03 17:10:57 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H

# define MINILIBX_H
# include "mlx.h"

# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
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
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_rect	rect;
}	t_texture;

typedef struct s_element
{
	t_texture	*texture;
	t_rect		rect;
	int			is_wall;
}	t_element;

void	init_texture(t_info_mlx	*info_mlx, t_texture *texture, int w, int h);
void	init_mlx(t_info_mlx	*info_mlx, int w, int h);
void	fill_rect(t_texture *texture, t_color color);
void	render_map(t_info_mlx *info_mlx, t_element *elements, int w, int h);
void	render_player(t_info_mlx *info_mlx, t_element *element);
void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY);

#endif
