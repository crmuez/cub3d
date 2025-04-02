/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-n <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:59:24 by dramos-n          #+#    #+#             */
/*   Updated: 2025/04/02 19:59:36 by dramos-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_player *player)
{
	double	angle;
	double	olddir_x;
	double	oldplane_x;

	angle = 0.1;
	olddir_x = player->dir_x;
	oldplane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = olddir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = oldplane_x * sin(angle) + player->plane_y * cos(angle);
}

void	rotate_right(t_player *player)
{
	double	angle;
	double	olddir_x;
	double	oldplane_x;

	angle = -0.1;
	olddir_x = player->dir_x;
	oldplane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = olddir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = oldplane_x * sin(angle) + player->plane_y * cos(angle);
}
