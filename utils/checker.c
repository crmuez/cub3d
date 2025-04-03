/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-n <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:33:03 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/03 17:33:06 by dramos-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_dir(char c)
{
	if (c == '0' || c == 'W' || c == 'N' || c == 'E' || c == 'S')
		return (1);
}

int	check_isspace(t_map *game)
{
	if ((ft_isspace(game->map[j + 1][i]))
		|| (ft_isspace(game->map[j - 1][i]))
		|| (ft_isspace(game->map[j][i + 1]))
		|| (ft_isspace(game->map[j][i - 1])))
		return (1);
}

int	check_chars(t_map *game)
{
	if (game->map[j][game->i] != '1' && game->map[j][game->i] != '0' &&
		game->map[j][game->i] != 'W' && game->map[j][game->i] != 'N' &&
		game->map[j][game->i] != 'E' && game->map[j][game->i] != 'S' &&
		game->map[j][game->i] != ' ')
		return (1);
}
