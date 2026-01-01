/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:11:24 by abdo              #+#    #+#             */
/*   Updated: 2025/11/22 12:48:21 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_map(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_whitespace(*s))
			s++;
		if (*s == '\0' || !ft_identif(*s))
			return (0);
		while (*s && *s != '\n')
			s++;
		while (*s && ft_whitespace(*s))
			s++;
		count++;
		if (count == 6)
		{
			if (*s == '1' && check_inside_map(s))
				return (1);
			return (0);
		}
	}
	return (0);
}

int	find_one(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == '1')
			return (i);
		i++;
	}
	return (0);
}

int	ft_direction(char c, t_player *player, int i, int j)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		player->player_x = (double)j + 0.5;
		player->player_y = (double)i + 0.5;
		return (1);
	}
	return (0);
}

int	safe_char_at(char **map, int i, int j, char flag)
{
	int	l;
	int	len;

	l = 0;
	while (map[l] != NULL)
		l++;
	if (i < 0 || j < 0 || i >= l)
		return (flag);
	len = ft_strlen(map[i]);
	if (j >= len)
		return (flag);
	return (map[i][j]);
}

int	check_spaces(char **map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = safe_char_at(map, i - 1, j, ' ');
	down = safe_char_at(map, i + 1, j, ' ');
	left = safe_char_at(map, i, j - 1, ' ');
	right = safe_char_at(map, i, j + 1, ' ');
	if ((up == '1' || up == ' ') && (down == '1' || down == ' ') && (left == '1'
			|| left == ' ') && (right == '1' || right == ' '))
		return (1);
	return (0);
}
