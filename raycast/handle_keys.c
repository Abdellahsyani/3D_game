/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:00:18 by asyani            #+#    #+#             */
/*   Updated: 2025/08/30 13:01:43 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	key_down(t_game *game, t_player *player)
{
	float	newx;
	float	newy;

	if (game->keys[KEY_S] || game->keys[KEY_DOWN])
	{
		newx = player->player_x - player->dir_x * MOVE_SPEED;
		newy = player->player_y - player->dir_y * MOVE_SPEED;
		if (player->map[(int)newy][(int)player->player_x] != '1')
			player->player_y = newy;
		if (player->map[(int)player->player_y][(int)newx] != '1')
			player->player_x = newx;
	}
}

void	handle_movement(t_game *game)
{
	t_player	*player;
	float		newx;
	float		newy;

	player = game->player;
	if (game->keys[KEY_LEFT] || game->keys[KEY_A])
		rotate_player(player, -ROT_SPEED);
	if (game->keys[KEY_RIGHT] || game->keys[KEY_D])
		rotate_player(player, ROT_SPEED);
	if (game->keys[KEY_W] || game->keys[KEY_UP])
	{
		newx = player->player_x + player->dir_x * MOVE_SPEED;
		newy = player->player_y + player->dir_y * MOVE_SPEED;
		if (player->map[(int)newy][(int)player->player_x] != '1')
			player->player_y = newy;
		if (player->map[(int)player->player_y][(int)newx] != '1')
			player->player_x = newx;
	}
	key_down(game, player);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode < 65536)
		game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

void	error_exit(char *msg, t_game *game)
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
	printf("%s\n", msg);
	exit(1);
}
