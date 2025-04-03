/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-n <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:45:32 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/03 17:45:33 by dramos-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_player *player, char **map)
{
	if (map[(int)(player->player_y)]
			[(int)(player->player_x + player->dir_x * 0.1)] != '1')
		player->player_x += player->dir_x * 0.1;
	if (map[(int)(player->player_y + player->dir_y * 0.1)]
			[(int)(player->player_x)] != '1')
		player->player_y += player->dir_y * 0.1;
}

void	move_backward(t_player *player, char **map)
{
	if (map[(int)(player->player_y)]
			[(int)(player->player_x - player->dir_x * 0.1)] != '1')
		player->player_x -= player->dir_x * 0.1;
	if (map[(int)(player->player_y - player->dir_y * 0.1)]
			[(int)(player->player_x)] != '1')
		player->player_y -= player->dir_y * 0.1;
}

void	strafe_left(t_player *player, char **map)
{
	int	new_x;
	int	new_y;

	new_x = (int)(player->player_x + player->plane_x * 0.1);
	new_y = (int)(player->player_y + player->plane_y * 0.1);
	if (map[(int)player->player_y][new_x] == '0')
		player->player_x -= player->plane_x * 0.1;
	if (map[new_y][(int)player->player_x] == '0')
		player->player_y -= player->plane_y * 0.1;
}

void	strafe_right(t_player *player, char **map)
{
	int	new_x;
	int	new_y;

	new_x = (int)(player->player_x + player->plane_x * 0.1);
	new_y = (int)(player->player_y + player->plane_y * 0.1);
	if (map[(int)player->player_y][new_x] == '0')
		player->player_x += player->plane_x * 0.1;
	if (map[new_y][(int)player->player_x] == '0')
		player->player_y += player->plane_y * 0.1;
}
