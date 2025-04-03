/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:03:35 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/25 15:34:36 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_character(int *character, char c)
{
	if (c == 'W' || c == 'E' || c == 'S' || c == 'N')
	{
		if (*character == 1)
			*character = 2;
		else if (*character == 0)
			*character = 1;
		if (*character == 2)
			return (ft_error('2'));
	}
	return (1);
}

int	check_letters(t_map *game)
{
	int	j;
	int	character;

	game->i = -1;
	j = -1;
	character = 0;
	while (game->map[++j])
	{
		while (game->map[j][++game->i] != '\n')
		{
			if (check_character(&character, game->map[j][game->i]) < 1)
				return (-1);
			if (check_chars(game) == 1)
			{
				free_map(game->map);
				return (ft_error('2'));
			}
		}
		game->i = -1;
	}
	if (character != 1)
		return (ft_error('2'));
	return (1);
}

int	check_valid_map(t_map *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (game->map[++j])
	{
		while (game->map[j][++i] != '\n')
		{
			if (check_dir(game->map[j][i]) == 1)
			{
				if (j == 0 || j == (game->maxlin_map - 1))
					return (ft_error('2'));
				else if (check_isspace(game) == 1)
					return (ft_error('2'));
			}
		}
		i = -1;
	}
	return (1);
}

int	check_error(char *argv, t_map *game)
{
	if (game->map && (check_letters(game) > 0)
		&& (check_valid_map(game) > 0))
	{
		if (save_rgb(game->ceiling, game->rgb_ceiling) < 0)
			return (-1);
		if (save_rgb(game->floor, game->rgb_floor) < 0)
			return (-1);
		return (1);
	}
	else
		return (-1);
}
