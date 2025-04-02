#include "../cub3d.h"

void	set_fc_color(t_map *game)
{
	game->math->floor_color = (game->rgb_floor[0] << 24) |
								(game->rgb_floor[1] << 16) |
								(game->rgb_floor[2] << 8) | 255;
    game->math->ceiling_color = (game->rgb_ceiling[0] << 24) |
								(game->rgb_ceiling[1] << 16) |
								(game->rgb_ceiling[2] << 8) |255;
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
	game->math->raydir_x = player->dir_x + player->plane_x * game->math->camera_x;
	game->math->raydir_y = player->dir_y + player->plane_y * game->math->camera_x;
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
	if (game->math->raydir_x < 0) {
		game->math->step_x = -1;
		game->math->sidedist_x = (player->player_x - game->math->map_x)*
			game->math->deltadist_x;
	} else {
		game->math->step_x = 1;
		game->math->sidedist_x = (game->math->map_x + 1.0 - player->player_x) *
			game->math->deltadist_x;
	}
	if (game->math->raydir_y < 0) {
		game->math->step_y = -1;
		game->math->sidedist_y = (player->player_y - game->math->map_y) *
			game->math->deltadist_y;
	} else {
		game->math->step_y = 1;
		game->math->sidedist_y = (game->math->map_y + 1.0 - player->player_y) *
			game->math->deltadist_y;
	}
}

void	calculate_hit(t_map *game)
{
	while (!(game->math->hit)) {
		if (game->math->sidedist_x < game->math->sidedist_y) {
			game->math->sidedist_x += game->math->deltadist_x;
			game->math->map_x += game->math->step_x;
			game->math->side = 0;
		} else {
			game->math->sidedist_y += game->math->deltadist_y;
			game->math->map_y += game->math->step_y;
			game->math->side = 1;
		}
		if (game->map[game->math->map_y][game->math->map_x] == '1') {
			game->math->hit = 1;
		}
	}
}

void	get_distances(t_map *game, t_player *player)
{
	if (game->math->side == 0) {
		game->math->perpdist = (game->math->map_x -player->player_x +
			(1 - game->math->step_x) / 2) / game->math->raydir_x;
	} else {
		game->math->perpdist = (game->math->map_y - player->player_y +
			(1 - game->math->step_y) / 2) / game->math->raydir_y;
	}
	game->math->line_height = (int)(HEIGHT / game->math->perpdist);
	game->math->draw_start = -(game->math->line_height) / 2 + HEIGHT / 2;
	game->math->draw_end = game->math->line_height / 2 + HEIGHT / 2;
}

void	draw_lines(t_map *game, t_player *player)
{
	get_distances(game, player);
	if (game->math->draw_start < 0) 
		game->math->draw_start = 0;
	if (game->math->draw_end >= HEIGHT) game->math->draw_end = HEIGHT - 1;

	if (game->math->side == 0) {
		game->math->wall_x = player->player_y +
			game->math->perpdist * game->math->raydir_y;
	} else {
		game->math->wall_x = player->player_x +
			game->math->perpdist * game->math->raydir_x;
	}
	game->math->wall_x -= floor(game->math->wall_x);
}

void	get_textures(t_map *game)
{
	if (game->math->side == 0) {
		if (game->math->raydir_x > 0)
			game->texture = game->w_wall;
		else
			game->texture = game->e_wall;
	} else {
		if (game->math->raydir_y > 0)
			game->texture = game->s_wall;
		else
			game->texture = game->n_wall;
	}
	game->math->tex_x = (int)(game->math->wall_x * game->texture->width);
	if ((game->math->side == 0 && game->math->raydir_x > 0) ||
		(game->math->side == 1 && game->math->raydir_y < 0))
		game->math->tex_x = game->texture->width - game->math->tex_x - 1;
}

void	draw_textures(t_map *game, mlx_image_t *img, int x)
{
	int	y;

	y = game->math->draw_start;
	while (y < game->math->draw_end)
	{
		game->math->tex_y = ((y - game->math->draw_start) *
			game->texture->height) / game->math->line_height;
		game->math->tex_index = (game->math->tex_y *
				game->texture->width + game->math->tex_x) * 4;
		game->math->color_r = game->texture->pixels[game->math->tex_index];
		game->math->color_g = game->texture->pixels[game->math->tex_index + 1];
		game->math->color_b = game->texture->pixels[game->math->tex_index + 2];
		game->math->color_full = (game->math->color_r << 24) |
			(game->math->color_g << 16) | (game->math->color_b << 8) | 255;
		mlx_put_pixel(img, x, y, game->math->color_full);
		y++;
	}
}

void	render_raycasting(mlx_image_t *img, t_player *player, t_map *game)
{
	int	x;

    game->texture = NULL;
    clear_image(img);
	draw_fc(game, img);
	x = 0;
	while (x++ < WIDTH)
	{
		init_rays(game, player, x);
		init_step(game, player);
		calculate_hit(game);
		draw_lines(game, player);
		get_textures(game);
		draw_textures(game, img, x);
	}
}