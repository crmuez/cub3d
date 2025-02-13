/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:33:36 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/13 19:08:32 by crmunoz-         ###   ########.fr       */
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
		return (ft_error('0'));
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) != 0)
		return (ft_error('3'));
	game = malloc(sizeof(t_map));
	if (!game)
		return (ft_error('1'));
	init_null(game);
	read_file(argv[1], game);
	save_texture(game);
	if (check_error(*argv, game) < 0)
		return (0);
	/*printf("EA: %s\n", game->ea_texture);
	printf("WE: %s\n", game->we_texture);
	printf("NO: %s\n", game->no_texture);
	printf("SO: %s\n", game->so_texture);
	printf("Floor: %s\n", game->floor);
	printf("Ceiling: %s\n", game->ceiling);
	int i = 0;
	while (game->map[i])
	{
		printf("%s", game->map[i]);
		i++;
	}*/
//printf("maparavilloso\n");
}
