/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-n <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:58:54 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/03 17:58:55 by dramos-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_fc_color(t_map *game)
{
	game->math->floor_color = (game->rgb_floor[0] << 24)
		| (game->rgb_floor[1] << 16) | (game->rgb_floor[2] << 8) | 255;
	game->math->ceiling_color = (game->rgb_ceiling[0] << 24)
		| (game->rgb_ceiling[1] << 16) | (game->rgb_ceiling[2] << 8) | 255;
}

void	draw_fc(t_map *game, mlx_image_t *img)
{
	int	y;
	int	x;

	set_fc_color(game);
	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			game->math->color = game->math->ceiling_color;
		else
			game->math->color = game->math->floor_color;
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, game->math->color);
			x++;
		}
		y++;
	}
}

void	init_rays(t_map *game, t_player *player, int x)
{
	game->math->camera_x = 2 * x / (double)WIDTH - 1;
	game->math->raydir_x = player->dir_x + player->plane_x
		* game->math->camera_x;
	game->math->raydir_y = player->dir_y + player->plane_y
		* game->math->camera_x;
	game->math->map_x = (int)player->player_x;
	game->math->map_y = (int)player->player_y;
	if (game->math->raydir_x == 0)
		game->math->deltadist_x = 1e30;
	else
		game->math->deltadist_x = fabs(1 / game->math->raydir_x);
	if (game->math->raydir_y == 0)
		game->math->deltadist_y = 1e30;
	else
		game->math->deltadist_y = fabs(1 / game->math->raydir_y);
	game->math->hit = 0;
}

void	init_step(t_map *game, t_player *player)
{
	if (game->math->raydir_x < 0)
	{
		game->math->step_x = -1;
		game->math->sidedist_x = (player->player_x - game->math->map_x)
			* game->math->deltadist_x;
	}
	else
	{
		game->math->step_x = 1;
		game->math->sidedist_x = (game->math->map_x + 1.0 - player->player_x)
			* game->math->deltadist_x;
	}
	if (game->math->raydir_y < 0)
	{
		game->math->step_y = -1;
		game->math->sidedist_y = (player->player_y - game->math->map_y)
			* game->math->deltadist_y;
	}
	else
	{
		game->math->step_y = 1;
		game->math->sidedist_y = (game->math->map_y + 1.0 - player->player_y)
			* game->math->deltadist_y;
	}
}

void	calculate_hit(t_map *game)
{
	while (!(game->math->hit))
	{
		if (game->math->sidedist_x < game->math->sidedist_y)
		{
			game->math->sidedist_x += game->math->deltadist_x;
			game->math->map_x += game->math->step_x;
			game->math->side = 0;
		}
		else
		{
			game->math->sidedist_y += game->math->deltadist_y;
			game->math->map_y += game->math->step_y;
			game->math->side = 1;
		}
		if (game->map[game->math->map_y][game->math->map_x] == '1')
		{
			game->math->hit = 1;
		}
	}
}
