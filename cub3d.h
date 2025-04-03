/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:11:24 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/27 17:33:32 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# define WIDTH	1024
# define HEIGHT	768

# include "./MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_player
{
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	direction;
}				t_player;

typedef struct s_math
{
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	uint32_t	color;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perpdist;
	int			step_x;
	int			step_y;
	int			hit;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			tex_index;
	uint8_t		color_r;
	uint8_t		color_g;
	uint8_t		color_b;
	uint32_t	color_full;
	int			side;
}				t_math;

typedef struct s_map
{
	char			**file;
	char			**map;
	int				maxlen_map;
	int				maxlin_map;
	mlx_texture_t	*n_wall;
	mlx_texture_t	*e_wall;
	mlx_texture_t	*w_wall;
	mlx_texture_t	*s_wall;
	mlx_texture_t	*texture;
	char			*no_tx;
	char			*so_tx;
	char			*we_tx;
	char			*ea_tx;
	char			*floor;
	long			rgb_floor[3];
	char			*ceiling;
	long			rgb_ceiling[3];
	int				i;
	mlx_image_t		*img;
	t_player		*player;
	t_math			*math;
	mlx_t			*mlx;
}				t_map;

/* UTILS */
int			ft_isspace(int c);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*get_next_line(int fd);
char		*ft_strdup(char *s1);
int			ft_strlen(char *s);
int			ft_strchr(char *s, int c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_error(int err);
void		free_map(char **map);
int			count_lines(char *argv);
char		*ft_strrchr(char *s, int c);
char		*fillspace(int len);
char		*ft_dupspace(char *s1, int len);
long		ft_atol(char *str);
char		**ft_split(char *s, char c);
void		init_null(t_map (*game));
void		clear_image(mlx_image_t *img);

/* CUB3D */
void		read_file(char *argv, t_map *game);

/* READ_MAP */
void		read_file(char *argv, t_map *game);
char		*ft_cpytexture(char *src);
char		*ft_cpyrgb(char *src);
int			begin_map(t_map *game, int i);
void		save_map(t_map *game, int i);

/* SAVE TEXTURES */
int			save_texture(t_map *game);
int			save_rgb(char *colors, long *rgb);
int			check_texture(t_map *game);

/* CHECK_ERROR */
int			check_error(char *argv, t_map *game);
void		ft_bzero(void *s, size_t n);

/* DIRECTION */
char		get_player_direction(t_player *player, char **map);
void		set_north(t_player *player);
void		set_west(t_player *player);
void		set_south(t_player *player);
void		set_east(t_player *player);

/* MOVEMENT */
void		move_forward(t_player *player, char **map);
void		move_backward(t_player *player, char **map);
void		strafe_left(t_player *player, char **map);
void		strafe_right(t_player *player, char **map);

/* CAMERA */
void		rotate_left(t_player *player);
void		rotate_right(t_player *player);

/* GAME */
void		close_hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		game_loop(void *param);
t_player	*init_player(char **map);
void		load_textures(t_map *game);

/* CEHCKER */
int			check_dir(char c);
int			check_isspace(t_map *game);
int			check_chars(t_map *game);

/* RAYCASTING */
void		render_raycasting(mlx_image_t *img, t_player *player, t_map *game);
void		set_fc_color(t_map *game);
void		draw_fc(t_map *game, mlx_image_t *img);
void		init_rays(t_map *game, t_player *player, int x);
void		init_step(t_map *game, t_player *player);
void		calculate_hit(t_map *game);

#endif
