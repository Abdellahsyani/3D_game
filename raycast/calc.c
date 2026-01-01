/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:05:49 by asyani            #+#    #+#             */
/*   Updated: 2025/10/05 10:07:31 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float	*direction(char c)
{
	float	*p;

	p = malloc(sizeof(int) * 2);
	if (c == 'N' || c == 'S')
	{
		p[0] = 0;
		if (c == 'N')
			p[1] = -1;
		else
			p[1] = 1;
		return (p);
	}
	if (c == 'E' || c == 'W')
	{
		p[1] = 0;
		if (c == 'W')
			p[0] = -1;
		else
			p[0] = 1;
		return (p);
	}
	return (0);
}

void	set_plane(t_player *player)
{
	if (player->direction == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->direction == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->direction == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	calc_step(t_player *player)
{
	if (player->raydi_x < 0)
	{
		player->step_x = -1;
		player->dsid_x = (player->player_x - player->map_x) * player->dx;
	}
	else
	{
		player->step_x = 1;
		player->dsid_x = (player->map_x + 1.0 - player->player_x) * player->dx;
	}
	if (player->raydi_y < 0)
	{
		player->step_y = -1;
		player->dsid_y = (player->player_y - player->map_y) * player->dy;
	}
	else
	{
		player->step_y = 1;
		player->dsid_y = (player->map_y + 1.0 - player->player_y) * player->dy;
	}
}

void	dda_algo(t_player *player)
{
	while (!player->hit)
	{
		if (player->dsid_x < player->dsid_y)
		{
			player->dsid_x += player->dx;
			player->map_x += player->step_x;
			player->side = 0;
		}
		else
		{
			player->dsid_y += player->dy;
			player->map_y += player->step_y;
			player->side = 1;
		}
		if (player->map[player->map_y][player->map_x] == '1')
			player->hit = 1;
	}
}

void	prep_calcs(t_player *player, int i)
{
	player->map_x = (int)player->player_x;
	player->map_y = (int)player->player_y;
	player->hit = 0;
	player->camera_x = 2 * (float)i / WIN_WIDTH - 1;
	player->raydi_x = player->dir_x + player->plane_x * player->camera_x;
	player->raydi_y = player->dir_y + player->plane_y * player->camera_x;
	if (player->raydi_x == 0)
		player->dx = 1e30;
	else
		player->dx = fabs(1 / player->raydi_x);
	if (player->raydi_y == 0)
		player->dy = 1e30;
	else
		player->dy = fabs(1 / player->raydi_y);
}
