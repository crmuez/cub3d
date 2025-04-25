/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:00:52 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/25 17:56:44 by crmunoz-         ###   ########.fr       */
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

void	free_struct(t_map *map)
{
	if (map == NULL)
		return ;
	free_texture(map->n_wall);
	free_texture(map->e_wall);
	free_texture(map->w_wall);
	free_texture(map->s_wall);
	free_string(map->no_tx);
	free_string(map->so_tx);
	free_string(map->we_tx);
	free_string(map->ea_tx);
	free_string(map->floor);
	free_string(map->ceiling);
	if (map->player != NULL)
		free(map->player);
	if (map->math != NULL)
		free(map->math);
	if (map->img != NULL)
		mlx_delete_image(map->mlx, map->img);
}
