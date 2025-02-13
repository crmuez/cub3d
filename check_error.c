/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:03:35 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/13 19:06:17 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_letters(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		while (game->map[j][i] != '\n')
		{
			if (game->map[j][i] != '1' && game->map[j][i] != '0'
				&& game->map[j][i] != 'W' && game->map[j][i] != 'N'
				&& game->map[j][i] != 'E' && game->map[j][i] != 'S'
				&& game->map[j][i] != ' ')
			{
				free_map(game->map);
				return (ft_error('2'));
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	check_valid_map(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[j])
	{
		while (game->map[j][i] != '\n')
		{
			if (game->map[j][i] == '0' || game->map[j][i] == 'W'
				|| game->map[j][i] == 'N' || game->map[j][i] == 'E'
				|| game->map[j][i] == 'S')
			{
				if (j == 0 || j == (game->maxlin_map - 1))
					return (ft_error('2'));
				else if ((ft_isspace(game->map[j + 1][i]))
				|| (ft_isspace(game->map[j - 1][i]))
				|| (ft_isspace(game->map[j][i + 1]))
				|| (ft_isspace(game->map[j][i - 1])))
					return (ft_error('2'));
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	check_error(char *argv, t_map *game)
{
	if (game->map && (check_letters(game) > 0)
		&& (check_valid_map(game) > 0))
		return (1);
	else
		return (-1);
}
