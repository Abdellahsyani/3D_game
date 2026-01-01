/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:18:45 by abdo              #+#    #+#             */
/*   Updated: 2025/11/22 15:32:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_side(char *s)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(s);
	if (!s || !*s)
		return (0);
	while (s[i] == ' ')
		i++;
	if (s[i] != '1')
		return (0);
	if (s[l - 1] == '1' || s[l - 1] == ' ')
		return (1);
	return (0);
}

int	fill_img(char *str, char *path, t_player *player)
{
	int	l;

	l = ft_strlen(path);
	while (l > 0)
	{
		if (path[l] == '.')
			break ;
		l--;
	}
	if (ft_strncmp(path + l, ".xpm", 4))
	{
		printf("the image should use .xpm extension\n");
		return (0);
	}
	if (*str == 'N')
		player->northimg = ft_strdup(path);
	else if (*str == 'S')
		player->southimg = ft_strdup(path);
	else if (*str == 'W')
		player->westimg = ft_strdup(path);
	else
		player->eastimg = ft_strdup(path);
	return (1);
}

int	open_fille(char *path, t_player *player)
{
	int	fd;

	(void)player;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		return (0);
	}
	return (fd);
}

int	path_checker(char *s, t_player *player)
{
	int		i;
	int		start;
	char	*path;

	i = 3;
	start = 0;
	path = NULL;
	skip_spaces(s, &i);
	start = i;
	if (s[i] == '\0')
		return (0);
	while (s[i] && s[i] != ' ')
		i++;
	path = ft_substr(s, start, i - start);
	if (!open_fille(path, player))
		return (0);
	skip_spaces(s, &i);
	if (s[i] != '\0')
		return (free(path), 0);
	if (!fill_img(s, path, player))
		return (free(path), 0);
	free(path);
	return (1);
}

int	check_inside_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_valid(str[i]) && str[i] != '\n')
			i++;
		if (str[i] != '\0' && str[i] != '\n' && !is_valid(str[i]))
			return (0);
		if (str[i] == '\0')
			break ;
		i++;
		if (str[i] == '\n')
		{
			while (str[i] && ft_whitespace(str[i]))
				i++;
			if (str[i] == '\0')
				return (1);
			return (0);
		}
	}
	return (1);
}
