/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:00:18 by asyani            #+#    #+#             */
/*   Updated: 2025/09/15 09:42:42 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode < 65536)
		game->keys[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

void	side_W_E(t_player *player, t_game *game, int column)
{
	if (player->raydiX > 0)
	{ 
		// West wall
		player->texWidth = game->west_width;
		player->texHeight = game->west_height;
		player->texAddr = (unsigned char *)game->west_addr;
		player->bpp = game->west_bpp / 8;
		player->lineLen = game->west_line_len;
	}
	else
{ 
		// East wall
		player->texWidth = game->east_width;
		player->texHeight = game->east_height;
		player->texAddr = (unsigned char *)game->east_addr;
		player->bpp = game->east_bpp / 8;
		player->lineLen = game->east_line_len;
	}
	player->texX = (int)(player->wallX * player->texWidth);
	if ((player->side == 0 && player->raydiX > 0) ||
		(player->side == 1 && player->raydiY < 0))
		player->texX = player->texWidth - player->texX - 1;
}

void	side_N_S(t_player *player, t_game *game, int column)
{
	if (player->raydiY > 0)
	{
		// North wall
		player->texWidth = game->north_width;
		player->texHeight = game->north_height;
		player->texAddr = (unsigned char *)game->north_addr;
		player->bpp = game->north_bpp / 8;
		player->lineLen = game->north_line_len;
	}
	else
{
		// South wall
		player->texWidth = game->south_width;
		player->texHeight = game->south_height;
		player->texAddr = (unsigned char *)game->south_addr;
		player->bpp = game->south_bpp / 8;
		player->lineLen = game->south_line_len;
	}
	player->texX = (int)(player->wallX * player->texWidth);
	if ((player->side == 0 && player->raydiX > 0) ||
		(player->side == 1 && player->raydiY < 0))
		player->texX = player->texWidth - player->texX - 1;
}

void	door_side(t_player *player, t_game *game, int column)
{
        int door_idx = find_door_idx(game, (int)player->mapX, (int)player->mapY);
        if (door_idx < 0) // safety: no such door
            return;
        player->texWidth      = game->door_width;
        player->texHeight     = game->door_height;
        player->texAddr       = (unsigned char *)game->door_addr;
        player->bpp = game->door_bpp / 8;
        player->lineLen       = game->door_line_len;

        /* base column inside door texture */
        player->texX = (int)(player->wallX * (float)player->texWidth);

        /* shift horizontally by door progress (0.0..1.0) to simulate sliding */
        player->texX += (int)(game->arr_door[door_idx].progress * (float)player->texWidth);
}

void draw_wall(t_game *game, t_player *player, int column)
{
	int y;

	char cell = player->map[(int)player->mapX][(int)player->mapY];
	y = player->start_draw;
	if (cell == 'D')
		door_side(player, game, column);
	else if (player->side == 0)
		side_W_E(player, game, column);
	else
		side_N_S(player, game, column);
	player->step = (float)player->texHeight / player->line_height;
	player->texPos = (player->start_draw - WIN_HEIGHT / 2.0f + player->line_height / 2.0f) * player->step;
	while (y < player->end_draw)
	{
		player->texY = (int)player->texPos;
		if (player->texY >= player->texHeight) player->texY = player->texHeight - 1;
		player->texPos += player->step;

		unsigned int color = *(unsigned int *)(player->texAddr + player->texY * player->lineLen + player->texX * player->bpp);
		put_pixel(&game->img, column, y, color);
		y++;
	}
}

int	to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_wall_column(t_game *game, t_player *player, int column)
{
	// get colors
	/*int roof_color = to_hex(player->roof[0], player->roof[1], player->roof[2]);*/
	/*int floor_color = to_hex(player->floor[0], player->floor[1], player->floor[2]);*/
	// Calculate line height and draw positions
	if (player->side == 0)
		player->wallp = player->dsidX - player->dx;
	else
		player->wallp = player->dsidY - player->dy;

	player->line_height = (int)(WIN_HEIGHT / player->wallp);
	player->start_draw = WIN_HEIGHT / 2 - player->line_height / 2;
	player->end_draw = WIN_HEIGHT / 2 + player->line_height / 2;

	if (player->start_draw < 0)
		player->start_draw = 0;
	if (player->end_draw >= WIN_HEIGHT)
		player->end_draw = WIN_HEIGHT - 1;


	if (player->side == 0)
	{
		player->wallX = player->playerY + player->wallp * player->raydiY;
		if (player->map[player->mapX][player->mapY] == 'D')
			player->wallX = player->y_door + player->wallp * player->raydiY;

	}
	else
{
		player->wallX = player->playerX + player->wallp * player->raydiX;
		if (player->map[player->mapX][player->mapY] == 'D')
			player->wallX = player->x_door + player->wallp * player->raydiX;

	}
	player->wallX -= floor(player->wallX);

	// Draw ceiling (above wall)
	for (int y = 0; y < player->start_draw; y++)
		put_pixel(&game->img, column, y, 0x8BE9FF);

	draw_wall(game, player, column);
	/*Draw_textures(game, player, column);*/

	// Draw floor (below wall)
	for (int y = player->end_draw; y < WIN_HEIGHT; y++)
		put_pixel(&game->img, column, y, 0xB7715C);
}

int	find_door_idx(t_game *game, int dx, int dy)
{
	int	i;

	i = 0;
	while(i < game->count_door)
	{
		if (game->arr_door[i].x_door == dx && game->arr_door[i].y_door == dy)
			return (i);
		i++;
	}
	return (-1);
}

void handle_movement(t_game *game)
{
	t_player *player;



	player = game->player;
	// Rotation (Left/Right arrows or A/D keys)
	if (game->keys[KEY_LEFT] || game->keys[KEY_A])
		rotate_player(player, -ROT_SPEED);

	if (game->keys[KEY_RIGHT] || game->keys[KEY_D])
		rotate_player(player, ROT_SPEED);

	if (game->keys[KEY_E])
	{
		float checkX = player->playerX + player->dirX * 1.5;
		float checkY = player->playerY + player->dirY * 1.5;
		int dx = (int)checkX;
		int dy = (int)checkY;
		if (player->map[dx][dy] == 'D')
		{
			int door_idx = find_door_idx(game, dx, dy);
			if (door_idx != -1)
			{
				game->arr_door[door_idx].is_opening = 1;
				game->arr_door[door_idx].is_closing = 0;
				player->idx = door_idx;
			}
		}
	}

	// Forward movement (W key)
	if (game->keys[KEY_W] || game->keys[KEY_UP])
	{
		float newX = player->playerX + player->dirX * MOVE_SPEED;
		float newY = player->playerY + player->dirY * MOVE_SPEED;

		// Check collision with walls and doors
		char cellY = player->map[(int)player->playerX][(int)newY];
		char cellX = player->map[(int)newX][(int)player->playerY];

		if (cellY != '1')
		{
			if (cellY == 'D')
			{
				int door_idx = find_door_idx(game, (int)player->playerX, (int)newY);
				if (door_idx != -1 && game->arr_door[door_idx].progress >= 0.5)
					player->playerY = newY;
			}
			else
			player->playerY = newY;
		}
		if (cellX != '1')
		{
			if (cellX == 'D')
			{
				int door_idx = find_door_idx(game, (int)newX, (int)player->playerY);
				if (door_idx != -1 && game->arr_door[door_idx].progress >= 0.5)
					player->playerX = newX;
			}
			else
			player->playerX = newX;
		}
	}
	// Backward movement (S key)
	if (game->keys[KEY_S] || game->keys[KEY_DOWN])
	{
		float newX = player->playerX - player->dirX * MOVE_SPEED;
		float newY = player->playerY - player->dirY * MOVE_SPEED;

		// Check collision with walls
		if (player->map[(int)player->playerX][(int)newY] != '1')
			player->playerY = newY;
		if (player->map[(int)newX][(int)player->playerY] != '1')
			player->playerX = newX;
	}
}
