/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:10:52 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/05 20:45:57 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char *argv)
{
	int		i;
	int		fd;
	char	*map;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (0);
	map = get_next_line(fd);
	i = 0;
	while (map)
	{
		free(map);
		i++;
		map = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	*clean_line(char *line)
{
	while (*line && *(line + 1))
	{
		if (*line == '.' && *(line + 1) == '/')
			return (line);
		line++;
	}
	return (NULL);
}

void	read_file(char *argv, t_map *game)
{
	int		i;
	int		fd;
	int		rows;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(1);
	rows = count_lines(argv);
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
	i = 0;
		while (game->file)
	{
		printf("%s\n", game->file[i]);
		i++;
	}
}
/*
	{
		while (ft_isspace(*line))
			line++;
		if (ft_strncmp("NO ", line, 3));
			game->no_texture = clean_line(&line);
		else if (ft_strncmp("SO ", line, 3));
			game->so_texture = clean_line(&line);
		else if (ft_strncmp("WE ", line, 3));
			game->we_texture = clean_line(&line);
		else if (ft_strncmp("EA ", line, 3));
			game->ea_texture = clean_line(&line);
		line = get_next_line(fd);
	}


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
}*/
/* 	PARA COMPROBAR QUE LA PRIMERA FILA Y LA ÚLTIMA SEAN 1's
		if (game->map[0][0] != '1'
			|| game->map[0][(ft_strlen(game->map)) - 1] != '1')
		{
			write(1, "Invalid map\n", 12);
			free_map(game->map);
			return (-1);
		}
*/