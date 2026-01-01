/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/11/22 18:17:09 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_arg(char *s)
{
	char	*str;

	str = ft_strrchr(s, '.');
	if (!str)
		return (-1);
	if (ft_strlen(str) > 4)
		return (-1);
	if (ft_strncmp(str, ".cub", 4) == 0)
		return (1);
	return (-1);
}

int	ft_valid_map(char **map, t_player *player)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (!ft_valid_id(map[i], player))
		{
			printf("Error: identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_init_player(t_player *player)
{
	player->northimg = NULL;
	player->southimg = NULL;
	player->eastimg = NULL;
	player->westimg = NULL;
	player->map = NULL;
}

int	ft_pars_map(char **map, t_player *player)
{
	if (!ft_valid_map(map, player) || !check_in_map(map, player))
	{
		ft_free(map);
		ft_free_path(player);
		printf("Error: inside map!\n");
		return (0);
	}
	ft_free(map);
	return (1);
}

int	pars_fun(int argc, char **argv, t_player *player)
{
	char	*str;
	char	**map;

	ft_init_player(player);
	if (argc != 2)
		return (1);
	if (check_arg(argv[1]) == -1)
	{
		printf("Error\n");
		return (1);
	}
	str = read_line(argv[1]);
	if (!str || !check_map(str))
	{
		printf("Error: unexcepted in map\n");
		return (free(str), 1);
	}
	map = ft_split(str, '\n');
	free(str);
	if (!map || !ft_pars_map(map, player))
		return (1);
	return (0);
}
