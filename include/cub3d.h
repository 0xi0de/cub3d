/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbetmall <lbetmall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:52 by lbetmall          #+#    #+#             */
/*   Updated: 2022/03/24 17:03:46 by lbetmall         ###   ########.fr       */
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
# define PI 3.14159265
# define FOV PI/2
# define RAY_DISTANCE 256000

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
	int			up;
	int			down;
	int			left;
	int			right;
	int			spawn_x;
	int			spawn_y;
	double		rotation;
	int			l_rotation;
	int			r_rotation;
	t_coord		pos;
}	t_player;

typedef struct s_info
{
	int			map_w;
	int			map_h;
	int			block_w;
	int			block_h;
	char		*path;
	t_info_mlx	mlx_info;
	t_texture	wall_texture[SCREEN_W];
	t_player	player;
	t_texture	wall_texture2D;
	t_texture	map3D;
	t_raycast	raycast;
	t_texture	map2D;
	t_element	floor;
	t_element	ceiling;
	t_element	map[];
}	t_info;

t_info	*init_info(int map_w, int map_h);
void	clear_img(t_texture *texture);
t_info	*parser(char *file);
void	fatal_error(void);
void	print_map(t_info *info);
int		dealkey(int key, t_info *info);
int		key_release(int key, t_info *info);
int		get_position(t_info *info, int x, int y);
int		check_wall(t_info *info, int x, int y);
void	raycastings(t_info *info, double angle);
void	*ft_calloc(unsigned long n);
char	**deltab(char **str);
void	free_tab(char **tab);
char	*delstr(char *str);
void	free_str(char *str);
void	ft_exit(t_info *info, int value, int **tab_int, char **tab_char);
void	render_map(t_info *info);
void	render_wall(t_info *info, int x, int y, int i, double angle);
void	render_2D_map(t_info *info);
void	draw_line(t_coord p1, t_coord p2, t_info *info);

#endif
