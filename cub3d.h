/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:11:24 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/18 18:15:47 by crmunoz-         ###   ########.fr       */
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

typedef struct s_map
{
	char		**file;
	char		**map;
	int			maxlen_map;
	int			maxlin_map;
	char		*no_tx;
	char		*so_tx;
	char		*we_tx;
	char		*ea_tx;
	char		*floor;
	long		rgb_floor[3];
	char		*ceiling;
	long		rgb_ceiling[3];
	mlx_t		*mlx;
}				t_map;

/* UTILS */
int		ft_isspace(int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_error(int err);
void	free_map(char **map);
int		count_lines(char *argv);
char	*ft_strrchr(char *s, int c);
char	*fillspace(int len);
char	*ft_dupspace(char *s1, int len);
long	ft_atol(char *str);
char	**ft_split(char *s, char c);

/* CUB3D */
void	read_file(char *argv, t_map *game);

/* READ_MAP */
void	read_file(char *argv, t_map *game);
char	*ft_cpytexture(char *src);
char	*ft_cpyrgb(char *src);
int		begin_map(t_map *game, int i);
void	save_map(t_map *game, int i);

/* SAVE TEXTURES */
void	save_texture(t_map *game);
int		save_rgb(char *colors, long *rgb);

/* CHECK_ERROR */
int		check_error(char *argv, t_map *game);

#endif
