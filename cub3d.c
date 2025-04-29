/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:33:36 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/04/29 20:49:13 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_raycasting(t_map *game)
{
	t_player	*player;
	t_math		*math;

	math = malloc(sizeof(t_math));
	if (!math)
		exit(1);
	player = init_player(game->map);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	game->player = player;
	game->math = math;
	load_textures(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_map	*game;

	if (argc != 2 || ft_strlen(argv[1]) < 5)
		return (ft_error('0'));
	if (!ft_strrchr(argv[1], '.')
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) != 0)
		return (ft_error('3'));
	read_file(argv[1], game);
	game = malloc(sizeof(t_map));
	if (!game)
		return (ft_error('1'));
	ft_bzero(game, sizeof(game));
	init_null(game);
	if (check_texture(game) < 0)
		ft_exit(game);
	if (save_texture(game) < 1)
		ft_exit(game);
	if (check_error(*argv, game) < 0)
		ft_exit(game);
	start_raycasting(game);
	return (0);
}

/*void print_map(t_map *game) {
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
}*/
