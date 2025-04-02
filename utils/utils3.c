/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-n <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:00:52 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/02 20:00:53 by dramos-n         ###   ########.fr       */
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
