/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:52 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/03 17:32:48 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "minilibx.h"
# define MALLOC_FAIL -1
# define SCREEN_W 800
# define SCREEN_H 800
# define WALL_W 100
# define WALL_H 100
# define PLAYER_W 20
# define PLAYER_H 20
# define KEYPRESS 2
# define RL_KEY 123
# define RR_KEY 124
# define KEYPRESSMASK (1L<<0)
# define FOV 3.14159265 / 2

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_raycast
{
	t_coord	start_point;
	t_coord	end_point;
}	t_raycast;

typedef struct s_player
{
	t_element	element;
	t_rect		hitbox;
	int			up;
	int			down;
	int			left;
	int			right;
	double		rotation;
	int			l_rotation;
	int			r_rotation;
}	t_player;

typedef struct s_info
{
	int			map_w;
	int			map_h;
	int			block_w;
	int			block_h;
	t_info_mlx	mlx_info;
	t_texture	wall_texture;
	t_texture	player_texture;
	t_player	player;
	t_raycast	raycast;
	t_element	map[];
}	t_info;

t_info	*init_info(int map_w, int map_h);
void	print_map(t_info *info);
int		dealkey(int key, t_info *info);
int		key_release(int key, t_info *info);
int		get_position(t_info *info, int x, int y);
int		check_wall(t_info *info, int x, int y);
void	raycasting(t_info *info, double angle);
void	raycastings(t_info *info, double angle);

#endif
