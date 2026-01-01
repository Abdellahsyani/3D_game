/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:22:27 by asyani            #+#    #+#             */
/*   Updated: 2025/10/01 10:07:40 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	run_game(t_player *player, t_game *game)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		prep_calcs(player, i);
		calc_step(player);
		dda_algo(player);
		draw_wall_column(game, player, i);
		i++;
	}
}

void	rotate_player(t_player *player, float angle)
{
	float	olddirx;
	float	oldplanex;

	olddirx = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = olddirx * sin(angle) + player->dir_y * cos(angle);
	oldplanex = player->plane_x;
	player->plane_x = player->plane_x * cos(angle)
		- player->plane_y * sin(angle);
	player->plane_y = oldplanex * sin(angle) + player->plane_y * cos(angle);
}

int	game_loop(t_game *game)
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
	int	i;

	i = 0;
	free_all(game);
	while (game->player->map[i])
	{
		free(game->player->map[i]);
		i++;
	}
	free(game->player->map);
	free(game->mlx);
	exit(0);
	return (0);
}
