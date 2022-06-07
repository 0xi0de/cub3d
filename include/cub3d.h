/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tallal-- <tallal--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:06:52 by lbetmall          #+#    #+#             */
/*   Updated: 2022/06/07 15:52:34 by tallal--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "minilibx.h"
# include <unistd.h>
# define MALLOC_FAIL -1
# define SCREEN_W 900
# define SCREEN_H 900
# define WALL_W 100
# define WALL_H 100
# define PLAYER_W 20
# define PLAYER_H 20
# define KEYPRESS 2
# define RL_KEY 65361
# define RR_KEY 65363
# define PI 3.14159265
# define FOV 0.78539816
# define RAY_DISTANCE 256000

typedef struct s_coord
{
	double	x;
	double	y;
	int		xi;
	int		yi;
}	t_coord;

typedef struct s_ratio
{
	float	ratio_x;
	float	ratio_y;
	int		final_x;
	float	final_y;
	float	size;
	int		index;
	int		dy;
}	t_ratio;

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

typedef struct s_line
{
	int		lenght;
	t_coord	raypoint;
	int		pos_x;
	char	orientation;
	int		endian;
	int		bpp;
	int		size_line;
	int		img_h;
	int		img_w;
	int		i;
}	t_line;

typedef struct s_info
{
	void		*img;
	char		*data_img;
	uint8_t		*pixel_img;
	t_line		line;
	int			map_w;
	int			map_h;
	int			block_w;
	int			block_h;
	int			index;
	int			coma_count;
	char		*path;
	t_info_mlx	mlx_info;
	t_player	player;
	t_texture	wall_texture2d;
	t_texture	map3d[4];
	t_raycast	raycast;
	t_texture	map2d;
	t_element	floor;
	t_element	ceiling;
	t_color		color_ceil;
	t_color		color_floor;
	t_element	map[];
}	t_info;

typedef struct s_parser
{
	char		**sprites;
	char		**map_txt;
	char		*line;
	int			fd;
	int			count;
}	t_parser;

t_info	*init_info(int map_w, int map_h, char **sprites, char **map_txt);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
int		tablen(char **tab);
char	**tabjoin(char **tab, char *str);
int		get_next_line(int fd, char **line);
char	*ft_strcpy(char *dest, char *src);
int		ft_atoi(char *str, t_info *info, char **sprites, char **map_txt);
int		ft_isspace(char c);
int		is_digit(char c);
double	find_tx(t_raycast ray, int x);
double	find_ty(t_raycast ray, int y);
void	handle_north_south(t_line line, t_ratio ratio, \
	t_texture texture, uint8_t *pixel_img);
void	handle_east_west(t_line line, t_ratio ratio, \
	t_texture texture, uint8_t *pixel_img);
void	final_free(t_info *info);
void	clear_img(t_info *info);
t_info	*parser(char *file);
void	fatal_error(void);
void	print_map(t_info *info);
int		dealkey(int key, t_info *info);
int		key_release(int key, t_info *info);
int		button_press(t_info *info);
int		get_position(t_info *info, int x, int y);
double	find_tx(t_raycast ray, int x);
double	find_ty(t_raycast ray, int y);
int		check_wall(t_info *info, int x, int y);
int		next_wall(t_info *info, int i, int *x_col, int *y_col);
void	raycastings(t_info *info, double angle);
void	*ft_calloc(unsigned long n);
char	**deltab(char **str);
void	free_tab(char **tab);
char	*delstr(char *str);
void	free_str(char *str);
void	put_player(t_info *info, int i, int j, char c);
void	render_map(t_info *info);
void	render_wall(t_info *info, int x, int y, double angle);
void	put_player(t_info *info, int i, int j, char c);
int		map_char_to_int(char c);
int		player_spawn(t_info *info, char **map_txt);
int		**fill_map_int(char **map_txt, int line_len, int nb_line);
int		valid_zero(int **map_int, int i, int j, int line_len);
int		check_map(int **map_int, int line_len);
void	fill_map_condition(t_info *info, int **map_int, int line_len, int i);
void	fill_map(t_info *info, int **map_int, int line_len, int nb_line);
int		parse_map(t_info *info, char **map_txt);
void	print_texture_error(int i);
t_info	*create_info(char **map_txt, char **sprites);
char	check_char(char *str, int *i);
void	handle_x(char **sprites, int fd, char *str);
int		fill_texture_condition(char c, char **sprites, char *str, int j);
void	fill_textures(char *str, int *count, char **sprites, int fd);
int		check_arg_map(char *str);

#endif
