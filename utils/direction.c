#include "../cub3d.h"

char	get_player_direction(t_player *player, char **map)
{
	int y;

	y = 0;
    while (map[y] != NULL) { 
        int x = 0;
        while (map[y][x] != '\0') {
            if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				player->direction = map[y][x];
				player->player_x = x + 0.5;
				player->player_y = y + 0.5;
			}
            x++;
        }
        y++;
    }
	return (0);
}

void set_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1.0;
	player->plane_x = 0.5;
	player->plane_y = 0;
}

void set_west(t_player *player)
{
	player->dir_x = -1.0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.5;
}

void set_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1.0;
	player->plane_x = -0.5;
	player->plane_y = 0;
}

void set_east(t_player *player)
{
	player->dir_x = 1.0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.5;
}