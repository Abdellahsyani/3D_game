/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:22:27 by asyani            #+#    #+#             */
/*   Updated: 2025/09/15 09:41:38 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

float *direction(char c)
{
	float *p = malloc(sizeof(int) * 2);
	if (c == 'N' || c == 'S')
	{
		p[0] = 0;
		if (c == 'N')
			p[1] = -1;
		else
			p[1] = 1;
		return p;
	}
	if (c == 'E' || c == 'W')
	{
		p[1] = 0;
		if (c == 'W')
			p[0] = -1;
		else
			p[0] = 1;
		return p;
	}
	return 0;
}

void	DDA_algo(t_player *player, t_game *game)
{
	while (!player->hit)
	{
		if (player->dsidX < player->dsidY)
		{
			player->dsidX += player->dx;
			player->mapX += player->stepX;
			player->side = 0;
		}
		else
	{
			player->dsidY += player->dy;
			player->mapY += player->stepY;
			player->side = 1;
		}
		if (player->map[player->mapX][player->mapY] == '1' || player->map[player->mapX][player->mapY] == 'D')
		{
			if (player->map[player->mapX][player->mapY] == 'D')
			{
				if (game->arr_door[player->idx].progress >= 0.5)
					continue;
				else
					player->hit = 1;
			}
			else
				player->hit = 1;
		}
	}
}

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	animate_door(t_game *game, double delta)
{
	int i;

	for (i = 0; i < game->count_door; i++)
	{
		t_door *door = &game->arr_door[i];

		if (door->is_opening)
			door->progress += delta * 0.001;
		else if (door->is_closing)
			door->progress -= delta * 0.001;

		if (door->progress >= 1.0)
		{
			door->progress = 1.0;
			door->is_opening = 0; 
		}
		if (door->progress <= 0.0)
		{
			door->progress = 0.0;
			door->is_closing = 0;
		}
	}
}


double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6; // seconds
}

void	run_game(t_player *player, t_game *game)
{
	// Cast rays for each column
	double current_time = get_time();
	double delta_time = current_time - game->last_frame_time;
	game->last_frame_time = current_time;
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		prep_calcs(player, i);
		calc_step(player);
		DDA_algo(player, game);
		animate_door(game, delta_time);
		//wall_calc(player);
		draw_wall_column(game, player, i);
	}
}

void rotate_player(t_player *player, float angle)
{
	// Rotate direction vector
	float oldDirX = player->dirX;
	player->dirX = player->dirX * cos(angle) - player->dirY * sin(angle);
	player->dirY = oldDirX * sin(angle) + player->dirY * cos(angle);


	//Rotate plane vector
	float oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = oldPlaneX * sin(angle) + player->planeY * cos(angle);	
}

void	init_player_direction(t_player *player)
{
	// Get initial direction
	float *p = direction(player->direction);
	if (!p)
	{
		printf("Yes");
		return;
	}
	player->dirX = p[0];
	player->dirY = p[1];
	free(p);

	// Set plane vector
	set_plane(player);
}

void	init_player(t_player *player, t_game *game)
{
	player->map = create_test_map();
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 30; y++)
		{
			if (player->map[x][y] == 'D')
			{
				game->arr_door[game->count_door].x_door = x;
				game->arr_door[game->count_door].y_door = y;
				game->arr_door[game->count_door].progress = 0.0;
				game->arr_door[game->count_door].is_opening = 0;
				game->arr_door[game->count_door].is_closing = 0;
				game->count_door++;
			}
			if (player->map[x][y] == 'N')
			{
				player->direction = 'N';
				player->playerX = (float)x;
				player->playerY = (float)y;
			}
			else if (player->map[x][y] == 'W')
			{
				player->playerX = (float)x;
				player->playerY = (float)y;
				player->direction = 'W';
			}
			else if (player->map[x][y] == 'E')
			{
				player->playerX = (float)x;
				player->playerY = (float)y;
				player->direction = 'E';
			}
			else if (player->map[x][y] == 'S')
			{
				player->direction = 'S';
				player->playerX = (float)x;
				player->playerY = (float)y;
			}
		}
	}
	init_player_direction(player);
}

int game_loop(t_game *game)
{
	handle_movement(game);
	render_frame(game);
	return (0);
}

void	render_frame(t_game *game)
{
	run_game(game->player, game);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->img.img, 0, 0);
}

int	close_window(t_game *game)
{
	exit(0);
	return (0);
}

void	load_textures(t_game *game)
{
	game->door_img =  mlx_xpm_file_to_image(game->mlx, "../textur/wall_2.xpm",
					 &game->door_width, &game->door_height);
	game->north_img = mlx_xpm_file_to_image(game->mlx, "../textur/wall_1.xpm",
					 &game->north_width, &game->north_height);
	game->south_img = mlx_xpm_file_to_image(game->mlx, "../textur/wall_1.xpm",
					 &game->south_width, &game->south_height);
	game->west_img = mlx_xpm_file_to_image(game->mlx, "../textur/red_wall.xpm",
					&game->west_width, &game->west_height);
	game->east_img = mlx_xpm_file_to_image(game->mlx, "../textur/wall.xpm",
					&game->east_width, &game->east_height);
	if (!game->north_img || !game->south_img || !game->west_img || !game->east_img)
		exit(1); ;
	game->door_addr = mlx_get_data_addr(game->door_img,
				     &game->door_bpp, &game->door_line_len, &game->door_endian);
	game->north_addr = mlx_get_data_addr(game->north_img,
				      &game->north_bpp, &game->north_line_len, &game->north_endian);
	game->south_addr = mlx_get_data_addr(game->south_img,
				      &game->south_bpp, &game->south_line_len, &game->south_endian);
	game->west_addr = mlx_get_data_addr(game->west_img,
				     &game->west_bpp, &game->west_line_len, &game->west_endian);
	game->east_addr = mlx_get_data_addr(game->east_img,
				     &game->east_bpp, &game->east_line_len, &game->east_endian);
	if (!game->north_addr || !game->south_addr || !game->west_addr || !game->east_addr)
		return ;
}

char	**create_test_map(void)
{
	char **map = malloc(sizeof(char*) * 10);

	map[0] = strdup("111111111111111111111111111111");
	map[1] = strdup("100001000000000000000001000001");
	map[2] = strdup("100000000100100000000000000001");
	map[3] = strdup("10100001111D111111011110000001");
	map[4] = strdup("10000001000000000D000000000001");
	map[5] = strdup("100000010000000001111100000001");
	map[6] = strdup("10000100000000000D000000000001");
	map[7] = strdup("100000000000N00001000000001001");
	map[8] = strdup("100000111100000001000000000001");
	map[9] = strdup("111111111111111111111111111111");

	return (map);
}

int main()
{
	return (init_cube());
}
