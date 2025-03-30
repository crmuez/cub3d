#include "../cub3d.h"

void render_raycasting(mlx_image_t *img, t_player *player, t_map *game)
{
    mlx_texture_t *texture = NULL;

    clear_image(img);

    uint32_t floor_color = (game->rgb_floor[0] << 24) | (game->rgb_floor[1] << 16) | (game->rgb_floor[2] << 8) | 255;
    uint32_t ceiling_color = (game->rgb_ceiling[0] << 24) | (game->rgb_ceiling[1] << 16) | (game->rgb_ceiling[2] << 8) | 255;

    for (int y = 0; y < HEIGHT; y++) {
        uint32_t color = (y < HEIGHT / 2) ? ceiling_color : floor_color;
        for (int x = 0; x < WIDTH; x++) {
            mlx_put_pixel(img, x, y, color);
        }
    }

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
            if (game->map[mapY][mapX] == '1') {
                hit = 1;
            }
        }

        if (side == 0) {
            perpWallDist = (mapX - player->player_x + (1 - stepX) / 2) / raydir_x;
        } else {
            perpWallDist = (mapY - player->player_y + (1 - stepY) / 2) / raydir_y;
        }

        int lineHeight = (int)(HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;

        if (drawStart < 0) drawStart = 0;
        if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        double wallX;
        if (side == 0) {
            wallX = player->player_y + perpWallDist * raydir_y;
        } else {
            wallX = player->player_x + perpWallDist * raydir_x;
        }
        wallX -= floor(wallX);

        if (side == 0) {
            texture = (raydir_x > 0) ? game->w_wall : game->e_wall;
        } else {
            texture = (raydir_y > 0) ? game->s_wall : game->n_wall;
        }

        int texX = (int)(wallX * texture->width);
        if ((side == 0 && raydir_x > 0) || (side == 1 && raydir_y < 0))
            texX = texture->width - texX - 1;

        for (int y = drawStart; y < drawEnd; y++) {
            int texY = ((y - drawStart) * texture->height) / lineHeight;
            int texIndex = (texY * texture->width + texX) * 4;

            uint8_t r = texture->pixels[texIndex];
            uint8_t g = texture->pixels[texIndex + 1];
            uint8_t b = texture->pixels[texIndex + 2];

            uint32_t color = (r << 24) | (g << 16) | (b << 8) | 255;
            mlx_put_pixel(img, x, y, color);
        }
    }
}