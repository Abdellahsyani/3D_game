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

void	Draw_textures(t_game *game, t_player *player, int column)
{

	// Draw wall
	char cell = player->map[(int)player->mapX][(int)player->mapY];
	if (player->side == 0)
	{
		if (cell == 'D')
		{
			int door_idx = find_door_idx(game, player->mapX, player->mapY);
			int texX = (int)(player->wallX * game->door_width);
			texX = texX + (int)(game->arr_door[door_idx].progress * game->door_width);
			if (texX >= game->door_width)
				return;
			for (int y = player->start_draw; y < player->end_draw; y++)
			{
				int texY = (int)(((y - player->start_draw) * game->door_height) / player->line_height);
				unsigned int color = *(unsigned int *)(game->door_addr + texY * game->door_line_len + texX * (game->door_bpp / 8));
				put_pixel(&game->img, column, y, color);
			}
			return;
		}
		if (player->raydiX > 0)
		{
			int texX = (int)(player->wallX * game->west_width);
			if ((player->side == 0 && player->raydiX > 0) || (player->side == 1 && player->raydiY < 0))
				texX = game->west_width - 1 - texX;

			for (int y = player->start_draw; y < player->end_draw; y++)
			{
				int texY = (int)(((y - player->start_draw) * game->west_height) / player->line_height);
				unsigned int color = *(unsigned int *)(game->west_addr + texY * game->west_line_len + texX * (game->west_bpp / 8));
				put_pixel(&game->img, column, y, color);
			}
		}
		else
	{
			int texX = (int)(player->wallX * game->east_width);
			for (int y = player->start_draw; y < player->end_draw; y++)
			{
				int texY = (int)(((y - player->start_draw) * game->east_height) / player->line_height);
				unsigned int color = *(unsigned int *)(game->east_addr + texY * game->east_line_len + texX * (game->east_bpp / 8));
				put_pixel(&game->img, column, y, color);
			}
		}
	}
	if (player->side == 1)
	{
		if (cell == 'D')
		{
			int door_idx = find_door_idx(game, player->mapX, player->mapY); // <--- USE THIS!
			int texX = (int)(player->wallX * game->door_width);
			texX = texX + (int)(game->arr_door[door_idx].progress * game->door_width);
			if (texX >= game->door_width)
				return;
			for (int y = player->start_draw; y < player->end_draw; y++)
			{
				int texY = (int)(((y - player->start_draw) * game->door_height) / player->line_height);
				unsigned int color = *(unsigned int *)(game->door_addr + texY * game->door_line_len + texX * (game->door_bpp / 8));
				put_pixel(&game->img, column, y, color);
			}
			return;
		}
		if (player->raydiY > 0)
		{
			int texX = (int)(player->wallX * game->north_width);
			for (int y = player->start_draw; y < player->end_draw; y++)
			{
				int texY = (int)(((y - player->start_draw) * game->north_height) / player->line_height);
				unsigned int color = *(unsigned int *)(game->north_addr + texY * game->north_line_len + texX * (game->north_bpp / 8));
				put_pixel(&game->img, column, y, color);
			}
		}
		else
	{
			int texX = (int)(player->wallX * game->south_width);
			if ((player->side == 0 && player->raydiX > 0) || (player->side == 1 && player->raydiY < 0))
				texX = game->south_width - 1 - texX;
			for (int y = player->start_draw; y < player->end_draw; y++)
			{
				int texY = (int)(((y - player->start_draw) * game->south_height) / player->line_height);
				unsigned int color = *(unsigned int *)(game->south_addr + texY * game->south_line_len + texX * (game->south_bpp / 8));
				put_pixel(&game->img, column, y, color);
			}
		}
	}
}

void	draw_wall_column(t_game *game, t_player *player, int column)
{
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

	Draw_textures(game, player, column);

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
