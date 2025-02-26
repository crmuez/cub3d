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

void move_forward(t_player *player)
{
	int map[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

    if (!map[(int)(player->playerY)][(int)(player->playerX + player->dirX * 0.1)])
        player->playerX += player->dirX * 0.1;
    if (!map[(int)(player->playerY + player->dirY * 0.1)][(int)(player->playerX)])
        player->playerY += player->dirY * 0.1;
}

void rotate_left(t_player *player)
{
    double oldDirX = player->dirX;
    player->dirX = player->dirX * cos(0.1) - player->dirY * sin(0.1);
    player->dirY = oldDirX * sin(0.1) + player->dirY * cos(0.1);
}


void close_hook(void *param) {
	mlx_terminate((mlx_t *)param);
}

void render_raycasting(mlx_image_t *img, t_player *player)
{

	int map[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

    for (int x = 0; x < WIDTH; x++)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = player->dirX + player->planeX * cameraX;
        double rayDirY = player->dirY + player->planeY * cameraX;

        int mapX = (int)player->playerX;
        int mapY = (int)player->playerY;

        double sideDistX, sideDistY;
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX, stepY;
        int hit = 0, side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player->playerX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->playerX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player->playerY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->playerY) * deltaDistY;
        }

        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapY][mapX] > 0)
                hit = 1;
        }

        perpWallDist = (side == 0) ? (mapX - player->playerX + (1 - stepX) / 2) / rayDirX
                                   : (mapY - player->playerY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;

        if (drawStart < 0) drawStart = 0;
        if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        for (int y = drawStart; y < drawEnd; y++)
            mlx_put_pixel(img, x, y, 0xFFFFFF);
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_player *player = (t_player *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_forward(player);
		if (keydata.key == MLX_KEY_A)
			rotate_left(player);
	}
	
}

void game_loop(void *param)
{
	t_player *player = malloc(sizeof(t_player));
	player->playerX = 5.0;
	player->playerY = 5.0;
	player->dirX = -1.0;
	player->dirY = 0.0;
	player->planeX = 0.0;
	player->planeY = 0.66;

	mlx_texture_t *texture = mlx_load_png("./assets/daniego2.png");
	if (!texture)
	{
		printf("Error: Failed to load texture\n");
		return;
	}

	mlx_image_t *img = mlx_texture_to_image((mlx_t *)param, texture);
	if (!img)
	{
		printf("Error: Failed to create image from texture\n");
		return;
	}

	mlx_delete_texture(texture);

	render_raycasting(img, player);
	mlx_image_to_window((mlx_t *)param, img, 0, 0);
}

void test_ray(t_map *game) {
	t_player *player = malloc(sizeof(t_player));
	player->playerX = 5.0;
	player->playerY = 5.0;
	player->dirX = -1.0;
	player->dirY = 0.0;
	player->planeX = 0.0;
	player->planeY = 0.66;

	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	mlx_key_hook(game->mlx, key_hook, player);
	mlx_loop_hook(game->mlx, game_loop, game->mlx);
	mlx_loop(game->mlx);
	free(player);
	mlx_terminate(game->mlx);
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
		//game->mlx = mlx_init(640, 480, "Cub3D", true);
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