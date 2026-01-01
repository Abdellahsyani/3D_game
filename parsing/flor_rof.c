/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flor_rof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:14:39 by abdo              #+#    #+#             */
/*   Updated: 2025/11/22 16:51:10 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_atoichecker(char **s, char *str, t_player *player)
{
	int	i;
	int	n;

	i = 0;
	while (s[i])
	{
		n = ft_atoi(s[i]);
		if (n < 0 || n > 255)
		{
			ft_free(s);
			return (0);
		}
		if (*(str - 2) == 'F')
			player->floor[i] = n;
		else
			player->roof[i] = n;
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_isdigit(char *range)
{
	int	start;

	start = 0;
	while (range[start])
	{
		if (!ft_isdigit(range[start]) && range[start] != ','
			&& range[start] != ' ')
			return (0);
		start++;
	}
	return (1);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

int	check_range(char *s, t_player *player)
{
	int		i;
	int		start;
	char	**arr;
	char	*range;

	i = 0;
	start = 0;
	skip_spaces(s, &i);
	start = i;
	if (s[i] == '\0')
		return (0);
	while (s[i])
		i++;
	range = ft_substr(s, start, i - start);
	if (!range || !check_isdigit(range))
	{
		free(range);
		return (0);
	}
	arr = ft_split(range, ',');
	free(range);
	if (!ft_atoichecker(arr, s, player))
		return (0);
	skip_spaces(s, &i);
	if (s[i] != '\0')
		return (0);
	ft_free(arr);
	return (1);
}
