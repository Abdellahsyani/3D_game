/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:40:56 by asyani            #+#    #+#             */
/*   Updated: 2025/10/02 18:11:00 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_arr(t_game *game)
{
	int		i;

	game->mlx = NULL;
	game->mlx_window = NULL;
	game->player = NULL;
	game->north_img = NULL;
	game->south_img = NULL;
	game->east_img = NULL;
	game->west_img = NULL;
	game->north_addr = NULL;
	game->south_addr = NULL;
	game->east_addr = NULL;
	game->west_addr = NULL;
	i = 0;
	while (i < 65536)
	{
		game->keys[i] = 0;
		i++;
	}
}

int	init_cube(t_player *player)
{
	t_game	game;

	init_arr(&game);
	init_player_direction(player);
	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("mlx failed", &game);
	game.mlx_window = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game.mlx_window)
		error_exit("mlx_window failed", &game);
	game.img.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.img.img)
		error_exit("Create image failed", &game);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
			&game.img.line_length, &game.img.endian);
	if (!game.img.addr)
		error_exit("image address failed", &game);
	game.player = player;
	load_textures(&game);
	mlx_hook(game.mlx_window, 2, 1, key_press, &game);
	mlx_hook(game.mlx_window, 3, 2, key_release, &game);
	mlx_hook(game.mlx_window, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

void	load_textures(t_game *game)
{
	game->north_img = mlx_xpm_file_to_image(game->mlx, game->player->northimg,
			&game->north_width, &game->north_height);
	game->south_img = mlx_xpm_file_to_image(game->mlx, game->player->southimg,
			&game->south_width, &game->south_height);
	game->west_img = mlx_xpm_file_to_image(game->mlx, game->player->westimg,
			&game->west_width, &game->west_height);
	game->east_img = mlx_xpm_file_to_image(game->mlx, game->player->eastimg,
			&game->east_width, &game->east_height);
	if (!game->north_img || !game->south_img || !game->west_img
		|| !game->east_img)
		error_exit("Load img failed", game);
	game->north_addr = mlx_get_data_addr(game->north_img, &game->north_bpp,
			&game->north_line_len, &game->north_endian);
	game->south_addr = mlx_get_data_addr(game->south_img, &game->south_bpp,
			&game->south_line_len, &game->south_endian);
	game->west_addr = mlx_get_data_addr(game->west_img, &game->west_bpp,
			&game->west_line_len, &game->west_endian);
	game->east_addr = mlx_get_data_addr(game->east_img, &game->east_bpp,
			&game->east_line_len, &game->east_endian);
	if (!game->north_addr || !game->south_addr || !game->west_addr
		|| !game->east_addr)
		error_exit("get textures address failed", game);
}

void	init_player_direction(t_player *player)
{
	float	*p;

	p = direction(player->direction);
	if (!p)
	{
		printf("Direction is not correct");
		return ;
	}
	player->dir_x = p[0];
	player->dir_y = p[1];
	free(p);
	set_plane(player);
}
