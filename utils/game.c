#include "../cub3d.h"

void close_hook(void *param)
{
	mlx_terminate((mlx_t *)param);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_map *game = (t_map *)param;

	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_forward(game->player, game->map);
		if (keydata.key == MLX_KEY_S)
			move_backward(game->player, game->map);
		if (keydata.key == MLX_KEY_A)
			strafe_left(game->player, game->map);
		if (keydata.key == MLX_KEY_D)
			strafe_right(game->player, game->map);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_right(game->player);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_left(game->player);
		if (keydata.key == MLX_KEY_ESCAPE)
			close_hook(param);
	}
}

void game_loop(void *param)
{
    t_map *game = (t_map *)param;
    clear_image(game->img);
    render_raycasting(game->img, game->player, game);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
}

t_player *init_player(char **map)
{
	t_player *player = malloc(sizeof(t_player));

	get_player_direction(player, map);
	if (player->direction == 'N')
		set_north(player);
	if (player->direction == 'S')
		set_south(player);
	if (player->direction == 'E')
		set_east(player);
	if (player->direction == 'W')
		set_west(player);
	return (player);
}

void load_textures(t_map *game)
{
	mlx_image_t *img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!img) {
		printf("Error: Failed to create image\n");
		return;
	}
	game->img = img;
	game->n_wall = mlx_load_png(game->no_tx);
	game->e_wall = mlx_load_png(game->ea_tx);
	game->w_wall = mlx_load_png(game->we_tx);
	game->s_wall = mlx_load_png(game->so_tx);
}