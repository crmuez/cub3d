/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:11:24 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/06 17:01:17 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

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
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	mlx_t		*mlx;
}			t_map;

/* UTILS */
int		ft_isspace(int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

/* CUB3D */
void	read_file(char *argv, t_map *game);

/* READ_MAP */
void	save_texture(t_map *game);
void	read_file(char *argv, t_map *game);

/* FREES */
int		ft_error(int err);
void	free_map(char **map);
char	*ft_strncpy(char *src);

#endif
