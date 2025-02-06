/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:33:36 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/06 17:10:22 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_null(t_map (*game))
{
	game->mlx = NULL;
	game->map = NULL;
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->ea_texture = NULL;
	game->we_texture = NULL;
}

int	main(int argc, char **argv)
{
	t_map	*game;

	if (argc != 2)
		return (ft_error(0));
	game = malloc(sizeof(t_map));
	if (!game)
		ft_error(1);
	init_null(game);
	write (1, "no peto aqui 1\n", 15);
	read_file(argv[1], game);
	write (1, "no peto aqui 2\n", 15);
	save_texture(game);
	write (1, "no peto aqui 5\n", 15);
	printf("EA: %s", game->ea_texture);
	printf("WE: %s", game->we_texture);
	printf("NO: %s", game->no_texture);
	printf("SO: %s", game->so_texture);
	write (1, "no peto aqui 6\n", 15);
}
