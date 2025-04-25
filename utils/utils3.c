/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:00:52 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/25 20:21:55 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	clear_image(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(img, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

void	free_texture(mlx_texture_t *texture)
{
	if (texture != NULL)
		mlx_delete_texture(texture);
}

void	free_string(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	free_struct(t_map *game)
{
	if (game == NULL)
		return ;
	free_texture(game->n_wall);
	free_texture(game->e_wall);
	free_texture(game->w_wall);
	free_texture(game->s_wall);
	free_string(game->no_tx);
	free_string(game->so_tx);
	free_string(game->we_tx);
	free_string(game->ea_tx);
	free_string(game->floor);
	free_string(game->ceiling);
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
	if (game->math != NULL)
		free(game->math);
	if (game->img != NULL)
		mlx_delete_image(game->mlx, game->img);
}
