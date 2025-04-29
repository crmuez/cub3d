/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:10:52 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/04/29 20:41:16 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_file(char *argv, t_map *game)
{
	int		i;
	int		fd;
	int		rows;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_error('5');
	rows = count_lines(argv);
	if (rows < 1)
		exit (1);
	game->file = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!game->file)
		free_map(game->file);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->file[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->file[i] = NULL;
}

char	*ft_cpytexture(char *src)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = 3;
	if (!src)
		return (NULL);
	while (src[len] && ft_isspace(src[len]))
		len++;
	i = len;
	while (!ft_isspace(src[len]))
		len++;
	len = len - i;
	dst = malloc(sizeof(char) * len + 1);
	len = 0;
	while (src[i] && (!ft_isspace(src[i])))
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	dst[len] = '\0';
	return (dst);
}

char	*ft_cpyrgb(char *src)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = 2;
	if (!src)
		return (NULL);
	while (src[len] && ft_isspace(src[len]))
		len++;
	i = len;
	while (src[len] != '\n')
		len++;
	len = len - i;
	dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (0);
	len = -1;
	while (src[i] && (src[i]) != '\n')
	{
		dst[++len] = src[i];
		i++;
	}
	dst[++len] = '\0';
	return (dst);
}

int	begin_map(t_map *game, int i)
{
	int	len_max;
	int	j;

	while (game->file[i])
	{
		if (game->file[i][0] == '\n')
			i++;
		else if (ft_strchr(game->file[i], '1') >= 0)
			break ;
		else
			return (-1);
	}
	j = i;
	len_max = ft_strlen(game->file[i]);
	while (game->file[i])
	{
		if (ft_strlen(game->file[i]) > len_max)
			len_max = ft_strlen(game->file[i]);
		i++;
	}
	game->maxlen_map = len_max;
	return (j);
}

void	save_map(t_map *game, int i)
{
	int	j;

	j = begin_map(game, i);
	while (game->file[i])
		i++;
	game->maxlin_map = i - j;
	game->map = (char **)malloc(sizeof(char *) * (game->maxlin_map + 1));
	i = 0;
	while (game->file[j])
	{
		game->map[i] = ft_dupspace(game->file[j], game->maxlen_map);
		i++;
		j++;
	}
	game->map[i] = NULL;
	if (game->map[0] == NULL)
		ft_error('2');
}

/*
void	check_texture(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			while (game->map[i][j] == '\t' || game->map[i][j] == '\n'
			|| game->map[i][j] == '\v' || game->map[i][j] == '\f'
			|| game->map[i][j] == '\r' || game->map[i][j] == ' ')
				j++;
			if (game->map[i][j] == 'N' && game->map[i][j + 1] == 'O')
				game->no_texture = game->map[i];
			else if (game->map[i][j] == 'S' && game->map[i][j + 1] == 'O')
				game->so_texture = game->map[i];
			else if (game->map[i][j] == 'W' && game->map[i][j + 1] == 'E')
				game->we_texture = game->map[i];
			else if (game->map[i][j] == 'E' && game->map[i][j + 1] == 'A')
				game->ea_texture = game->map[i];
		}
		j = 0;
		i++;
	}
}
*/

/* 	PARA COMPROBAR QUE LA PRIMERA FILA Y LA ÚLTIMA SEAN 1's
		if (game->map[0][0] != '1'
			|| game->map[0][(ft_strlen(game->map)) - 1] != '1')
		{
			write(1, "Invalid map\n", 12);
			free_map(game->map);
			return (-1);
		}
*/

/*
char	*clean_line(char *line)
{
	while (*line && *(line + 1))
	{
		if (*line == '.' && *(line + 1) == '/')
			return (line);
		line++;
	}
	return (NULL);
}*/