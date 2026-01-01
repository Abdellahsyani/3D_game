/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:47:08 by asyani            #+#    #+#             */
/*   Updated: 2025/10/01 10:01:12 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	wall_height(t_player *player, int *r_color, int *f_color)
{
	*r_color = to_hex(player->roof[0], player->roof[1], player->roof[2]);
	*f_color = to_hex(player->floor[0], player->floor[1], player->floor[2]);
	player->line_height = (int)(WIN_HEIGHT / player->wallp);
	player->start_draw = WIN_HEIGHT / 2 - player->line_height / 2;
	player->end_draw = WIN_HEIGHT / 2 + player->line_height / 2;
	if (player->start_draw < 0)
		player->start_draw = 0;
	if (player->end_draw >= WIN_HEIGHT)
		player->end_draw = WIN_HEIGHT - 1;
	if (player->side == 0)
		player->wall_x = player->player_y + player->wallp * player->raydi_y;
	else
		player->wall_x = player->player_x + player->wallp * player->raydi_x;
	player->wall_x -= floor(player->wall_x);
}

void	draw_wall_column(t_game *game, t_player *player, int column)
{
	int	y;
	int	roof_color;
	int	floor_color;

	if (player->side == 0)
		player->wallp = player->dsid_x - player->dx;
	else
		player->wallp = player->dsid_y - player->dy;
	if (player->wallp < 1e-6)
		player->wallp = 1e-6;
	wall_height(player, &roof_color, &floor_color);
	y = 0;
	while (y < player->start_draw)
	{
		put_pixel(&game->img, column, y, roof_color);
		y++;
	}
	draw_wall(game, player, column);
	y = player->end_draw;
	while (y < WIN_HEIGHT)
	{
		put_pixel(&game->img, column, y, floor_color);
		y++;
	}
}

void	free_all(t_game *game)
{
	if (game->north_img)
		mlx_destroy_image(game->mlx, game->north_img);
	if (game->south_img)
		mlx_destroy_image(game->mlx, game->south_img);
	if (game->east_img)
		mlx_destroy_image(game->mlx, game->east_img);
	if (game->west_img)
		mlx_destroy_image(game->mlx, game->west_img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->player->northimg)
		free(game->player->northimg);
	if (game->player->southimg)
		free(game->player->southimg);
	if (game->player->westimg)
		free(game->player->westimg);
	if (game->player->eastimg)
		free(game->player->eastimg);
	if (game->mlx_window)
		mlx_destroy_window(game->mlx, game->mlx_window);
	mlx_destroy_display(game->mlx);
}
