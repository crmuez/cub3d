/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:33:36 by crmunoz-          #+#    #+#             */
/*   Updated: 2025/02/27 17:39:45 by crmunoz-         ###   ########.fr       */
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

    if (!map[(int)(player->player_y)][(int)(player->player_x + player->dir_x * 0.1)])
        player->player_x += player->dir_x * 0.1;
    if (!map[(int)(player->player_y + player->dir_y * 0.1)][(int)(player->player_x)])
        player->player_y += player->dir_y * 0.1;
}

void rotate_left(t_player *player)
{
    double olddir_x = player->dir_x;
    player->dir_x = player->dir_x * cos(0.1) - player->dir_y * sin(0.1);
    player->dir_y = olddir_x * sin(0.1) + player->dir_y * cos(0.1);
}


void close_hook(void *param) {
	mlx_terminate((mlx_t *)param);
}

void clear_image(mlx_image_t *img)
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			mlx_put_pixel(img, x, y, 0xFF0000);
		}
	}
}

void render_raycasting(mlx_image_t *img, t_player *player, t_map *game) {
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

	clear_image(img);
	for (int x = 0; x < WIDTH; x++) {
		double camera_x = 2 * x / (double)WIDTH - 1;
		double raydir_x = player->dir_x + player->plane_x * camera_x;
		double raydir_y = player->dir_y + player->plane_y * camera_x;

		int mapX = (int)player->player_x;
		int mapY = (int)player->player_y;

		double sideDistX, sideDistY;
		double deltaDistX = (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
		double deltaDistY = (raydir_y == 0) ? 1e30 : fabs(1 / raydir_y);
		double perpWallDist;

		int stepX, stepY;
		int hit = 0, side;

		if (raydir_x < 0) {
			stepX = -1;
			sideDistX = (player->player_x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->player_x) * deltaDistX;
		}
		if (raydir_y < 0) {
			stepY = -1;
			sideDistY = (player->player_y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->player_y) * deltaDistY;
		}

		while (!hit) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map[mapY][mapX] > 0) hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - player->player_x + (1 - stepX) / 2) / raydir_x;
		else
			perpWallDist = (mapY - player->player_y + (1 - stepY) / 2) / raydir_y;

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;

		if (drawStart < 0) drawStart = 0;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		double wallX = (side == 0) ? player->player_y + perpWallDist * raydir_y
								   : player->player_x + perpWallDist * raydir_x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * game->wall->width);
		if ((side == 0 && raydir_x > 0) || (side == 1 && raydir_y < 0))
			texX = game->wall->width - texX - 1;

		for (int y = drawStart; y < drawEnd; y++) {
			int texY = ((y - drawStart) * game->wall->height) / (drawEnd - drawStart);
			int texIndex = (texY * game->wall->width + texX) * 4;

			uint8_t r = game->wall->pixels[texIndex];
			uint8_t g = game->wall->pixels[texIndex + 1];
			uint8_t b = game->wall->pixels[texIndex + 2];

			uint32_t color = (r << 24) | (g << 16) | (b << 8) | 255;
			mlx_put_pixel(img, x, y, color);
		}
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

void game_loop(void *param) {
    t_map *game = (t_map *)param;
    clear_image(game->img);
    render_raycasting(game->img, game->player, game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void test_ray(t_map *game) {
	t_player *player = malloc(sizeof(t_player));
	player->player_x = 3.5;
	player->player_y = 3.5;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.66 * player->dir_y;
	player->plane_y = -0.66 * player->dir_x;

	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	game->player = player;

	mlx_image_t *img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img) {
		printf("Error: Failed to create image\n");
		return;
	}
	game->img = img;
	game->wall = mlx_load_png("assets/daniego2.png");

	mlx_key_hook(game->mlx, key_hook, player);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free(game->player);
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
		test_ray(game);
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