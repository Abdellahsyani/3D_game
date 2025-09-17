/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 09:34:56 by asyani            #+#    #+#             */
/*   Updated: 2025/09/15 09:41:50 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	set_plane(t_player *player)
{
	if (player->direction == 'N')
	{
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if (player->direction == 'S')
	{
		player->planeX = -0.66;
		player->planeY = 0;
	}
	else if (player->direction == 'E')
	{
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->planeX = 0;
		player->planeY = -0.66;
	}
}

void	calc_step(t_player *player)
{
	// Calculate step and initial sideDist
	if (player->raydiX < 0)
	{
		player->stepX = -1;
		player->dsidX = (player->playerX - player->mapX) * player->dx;
	}
	else
	{
		player->stepX = 1;
		player->dsidX = (player->mapX + 1.0 - player->playerX) * player->dx;
	}
	if (player->raydiY < 0)
	{
		player->stepY = -1;
		player->dsidY = (player->playerY - player->mapY) * player->dy;
	}
	else
	{
		player->stepY = 1;
		player->dsidY = (player->mapY + 1.0 - player->playerY) * player->dy;
	}
}

void	prep_calcs(t_player *player, int i)
{
	player->mapX = (int)player->playerX;
	player->mapY = (int)player->playerY;

	player->hit = 0;
	player->cameraX = 2 * (float)i / WIN_WIDTH - 1;
	player->raydiX = player->dirX + player->planeX * player->cameraX;
	player->raydiY = player->dirY + player->planeY * player->cameraX;

	// Calculate delta distances
	if (player->raydiX == 0)
		player->dx = 1e30;
	else
		player->dx = fabs(1 / player->raydiX);

	if (player->raydiY == 0)
		player->dy = 1e30;
	else
		player->dy = fabs(1 / player->raydiY);
}

int init_cube(void)
{
	t_game      game;
	t_player    player;
	int         i;

	game.count_door = 0;
	// Initialize key states
	i = 0;
	while (i < 65536)
	{
		game.keys[i] = 0;
		i++;
	}

	// Initialize player
	init_player(&player, &game);

	// Initialize MLX
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);

	game.mlx_window = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game.mlx_window)
		return (1);

	// Create image
	game.img.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, 
				   &game.img.line_length, &game.img.endian);

	game.player = &player;
	load_textures(&game);

	// Set up event hooks
	mlx_hook(game.mlx_window, 2, 1L<<0, key_press, &game);
	mlx_hook(game.mlx_window, 3, 1L<<1, key_release, &game);
	mlx_hook(game.mlx_window, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);

	mlx_loop(game.mlx);
	return (0);
}
