/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:11:24 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/05 14:39:24 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
/* CUB3D */
int		read_file(char *argv, t_map *game);

#endif
