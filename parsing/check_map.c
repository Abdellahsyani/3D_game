/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:03:11 by abdo              #+#    #+#             */
/*   Updated: 2025/11/22 18:19:41 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	checkup_down(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '1')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_side(char **str, int count)
{
	int	i;
	int	l;

	i = 1;
	l = 0;
	while (str[l] != NULL)
		l++;
	while (str[i] && i < (l - count))
	{
		if (!ft_side(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_spaces(char **str, int i, int j)
{
	if (str[i][j] == ' ')
	{
		if (!check_spaces(str, i, j))
		{
			printf("Error: check spaces!");
			return (0);
		}
	}
	return (1);
}

int	duplicatid(char **str, t_player *player)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_direction(str[i][j], player, i, j))
			{
				count++;
				player->direction = str[i][j];
			}
			if (!ft_spaces(str, i, j) || !check_zero(str, i, j) || count > 1)
				return (0);
			j++;
		}
		i++;
	}
	if (count == 0)
		return (0);
	return (1);
}

int	check_in_map(char **map, t_player *player)
{
	char	**str;
	int		n;
	int		i;
	int		count;

	count = 0;
	n = 0;
	n = find_one(map);
	if (n == 0)
		return (0);
	str = map + n;
	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] != NULL)
		i++;
	count = get_only_map(str, &i);
	if (i > 0 && (!checkup_down(str[0]) || !checkup_down(str[i])
			|| !check_side(str, count)))
		return (0);
	if (!duplicatid(str, player))
		return (0);
	fill_map(str, player);
	return (1);
}
