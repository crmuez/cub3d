/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:33:11 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/24 18:11:16 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_rgb(char **token) //no funciona
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (token[j])
	{
		while (token[j][i])
		{
			while (token[j][i] == ' ' && token[j][i + 1])
				i++;
			if (token[j][i] == ' ')
				return (1);
			printf ("c:%c, i: %i\n", token[j][i], token[j][i]);
			if (token[j][i] < 48 || token[j][i] > 57)
				return (ft_error('4'));
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	save_rgb(char *colors, long *rgb)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = ft_split(colors, ',');
	if (!tokens || (check_rgb(tokens) < 0))
		return (-1);
	while (tokens[i] && i < 3)
	{
		rgb[i] = ft_atol(tokens[i]);
		if (rgb[i] < 0 || rgb[i] >= 256)
		{
			free(tokens[i]);
			free(tokens);
			return (ft_error('4'));
		}
		free(tokens[i]);
		i++;
	}
	if (tokens)
		free(tokens);
	return (1);
}

int	check_texture(t_map *game)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (game->file[++i])
	{
		if (!ft_strncmp("NO ", game->file[i], 3))
			n++;
		else if (!ft_strncmp("SO ", game->file[i], 3))
			n++;
		else if (!ft_strncmp("WE ", game->file[i], 3))
			n++;
		else if (!ft_strncmp("EA ", game->file[i], 3))
			n++;
		else if (!ft_strncmp("F ", game->file[i], 2))
			n++;
		else if (!ft_strncmp("C ", game->file[i], 2))
			n++;
	}
	if (n != 6)
		return (ft_error('2'));
	return (1);
}

int	save_texture(t_map *game)
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
			break ;
	}
	if (!game->file[i + 1])
		return (ft_error('2'));
	save_map(game, (i + 1));
	return (1);
}
