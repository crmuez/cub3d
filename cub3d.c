/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:33:36 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/25 15:29:56 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_vertical_line(mlx_image_t* img, int x, int start_y, int end_y, uint32_t color) {
    if (!img) return;

    for (int y = start_y; y <= end_y; y++) {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            mlx_put_pixel(img, x, y, color);
        }
    }
}

void test_ray(t_map *game) {
	
	int worldMap[24][24]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	double posX = 22, posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	
	mlx_image_t* img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	
	
    // Draw a vertical line at x = 320 from y = 100 to y = 380 with a red color
    draw_vertical_line(img, 320, 100, 380, 0xFF0000FF);
	
    // Render the image
    mlx_image_to_window(game->mlx, img, 0, 0);
	
	mlx_loop(game->mlx);
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
	ft_bzero(game, sizeof(game));
	read_file(argv[1], game);
	if (check_texture(game) < 0)
		return (0);
	if (save_texture(game) < 1)
		return (0);
	if (check_error(*argv, game) > 0)
	{
		game->mlx = mlx_init(640, 480, "Cub3D", true);
		test_ray(game);
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