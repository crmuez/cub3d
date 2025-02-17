/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:33:36 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/17 18:18:01 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_null(t_map (*game))
{
	game->file = NULL;
	game->mlx = NULL;
	game->map = NULL;
	game->no_tx = NULL;
	game->so_tx = NULL;
	game->ea_tx = NULL;
	game->we_tx = NULL;
	game->floor = NULL;
	game->ceiling = NULL;
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
	if (check_error(*argv, game) > 0)
	{
		game->mlx = mlx_init(HEIGHT, WIDTH, "Cub3D", true);
		//mlx_key_hook(game->mlx, &my_keyhook, game);
		//mlx_loop(game->mlx);
		//mlx_terminate(game->mlx);
	}
	return (0);
}
//print_map(game);
/*
printf("EA: %s\n", game->ea_tx);
printf("WE: %s\n", game->we_tx);
printf("NO: %s\n", game->no_tx);
printf("SO: %s\n", game->so_tx);
printf("Floor: r%lig%lib%li\n", game->rgb_floor[0], game->rgb_floor[1], game->rgb_floor[2]);
printf("Ceiling:r%lig%lib%li\n", game->rgb_ceiling[0], game->rgb_ceiling[1], game->rgb_ceiling[2]);
int i = 0;
while (game->map[i])
{
	printf("%s", game->map[i]);
	i++;
}

*/