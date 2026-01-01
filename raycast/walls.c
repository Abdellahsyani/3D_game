/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:58:11 by asyani            #+#    #+#             */
/*   Updated: 2025/10/01 10:02:33 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	prep_texx(t_player *player, int *texX)
{
	*texX = (int)(player->wall_x * player->tex_width);
	if ((player->side == 0 && player->raydi_x > 0)
		|| (player->side == 1 && player->raydi_y < 0))
		*texX = player->tex_width - *texX - 1;
	player->step = (float)player->tex_height / player->line_height;
	player->tex_pos = (player->start_draw - WIN_HEIGHT / 2.0f
			+ player->line_height / 2.0f) * player->step;
}

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	side_w_e(t_player *player, t_game *game)
{
	if (player->raydi_x > 0)
	{
		player->tex_width = game->west_width;
		player->tex_height = game->west_height;
		player->tex_addr = (unsigned char *)game->west_addr;
		player->bpp = game->west_bpp / 8;
		player->line_len = game->west_line_len;
	}
	else
	{
		player->tex_width = game->east_width;
		player->tex_height = game->east_height;
		player->tex_addr = (unsigned char *)game->east_addr;
		player->bpp = game->east_bpp / 8;
		player->line_len = game->east_line_len;
	}
}

void	side_n_s(t_player *player, t_game *game)
{
	if (player->raydi_y > 0)
	{
		player->tex_width = game->north_width;
		player->tex_height = game->north_height;
		player->tex_addr = (unsigned char *)game->north_addr;
		player->bpp = game->north_bpp / 8;
		player->line_len = game->north_line_len;
	}
	else
	{
		player->tex_width = game->south_width;
		player->tex_height = game->south_height;
		player->tex_addr = (unsigned char *)game->south_addr;
		player->bpp = game->south_bpp / 8;
		player->line_len = game->south_line_len;
	}
}

void	draw_wall(t_game *game, t_player *player, int column)
{
	int				texx;
	int				texy;
	int				y;
	unsigned int	color;

	y = player->start_draw;
	if (player->side == 0)
		side_w_e(player, game);
	else
		side_n_s(player, game);
	prep_texx(player, &texx);
	while (y < player->end_draw)
	{
		texy = (int)player->tex_pos;
		if (texy >= player->tex_height)
			texy = player->tex_height - 1;
		player->tex_pos += player->step;
		color = *(unsigned int *)(player->tex_addr + texy * player->line_len
				+ texx * player->bpp);
		put_pixel(&game->img, column, y, color);
		y++;
	}
}
