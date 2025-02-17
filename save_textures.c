/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:33:11 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/14 16:10:52 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_rgb(char *colors, long *rgb)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = ft_split(colors, ',');
	if (!tokens)
		return (-1);
	while (tokens[i] && i < 3)
	{
		rgb[i] = ft_atol(tokens[i]);
		if (rgb[i] < 0 || rgb[i] >= 256)
		{
			free_map(tokens);
			return (ft_error('4'));
		}
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (1);
}

void	save_texture(t_map *game)
{
	int	i;

	i = -1;
	while (game->file[++i])
	{
		if (!ft_strncmp("NO ", game->file[i], 3))
			game->no_tx = ft_cpytexture(game->file[i]);
		else if (!ft_strncmp("SO ", game->file[i], 3))
			game->so_tx = ft_cpytexture(game->file[i]);
		else if (!ft_strncmp("WE ", game->file[i], 3))
			game->we_tx = ft_cpytexture(game->file[i]);
		else if (!ft_strncmp("EA ", game->file[i], 3))
			game->ea_tx = ft_cpytexture(game->file[i]);
		else if (!ft_strncmp("F ", game->file[i], 2))
			game->floor = ft_cpyrgb(game->file[i]);
		else if (!ft_strncmp("C ", game->file[i], 2))
			game->ceiling = ft_cpyrgb(game->file[i]);
		if (game->no_tx && game->so_tx && game->ea_tx
			&& game->we_tx && game->ceiling && game->floor)
		{
			save_map(game, (i + 1));
			break ;
		}
	}
}
