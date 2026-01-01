/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:07:43 by abdo              #+#    #+#             */
/*   Updated: 2025/10/04 11:56:23 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	open_file(char *s)
{
	if (!s)
		return (-1);
	return (open(s, O_RDONLY));
}

int	identif_checker(char *s1, char *s2, t_player *player)
{
	while (*s1 == ' ')
		s1++;
	if (*s1 == *s2)
	{
		if (ft_strncmp(s1, s2, 3))
			return (0);
		if (!path_checker(s1, player))
			return (0);
	}
	return (1);
}

int	check_singlid(char *s, t_player *player)
{
	while (*s && *s == ' ')
		s++;
	if (*s == 'F')
	{
		if (ft_strncmp(s, "F ", 2))
			return (0);
		if (!check_range(s + 2, player))
			return (0);
	}
	if (*s == 'C')
	{
		if (ft_strncmp(s, "C ", 2))
			return (0);
		if (!check_range(s + 2, player))
			return (0);
	}
	return (1);
}

char	*ft_idchar(char c)
{
	if (c == 'S')
		return (ft_strdup("SO "));
	if (c == 'N')
		return (ft_strdup("NO "));
	if (c == 'W')
		return (ft_strdup("WE "));
	if (c == 'E')
		return (ft_strdup("EA "));
	return (NULL);
}

int	ft_valid_id(char *str, t_player *player)
{
	int		i;
	char	*identif;

	i = 0;
	identif = NULL;
	skip_spaces(str, &i);
	if (ft_identif(str[i]))
	{
		if (str[i] == 'S' || str[i] == 'W' || str[i] == 'N' || str[i] == 'E')
		{
			identif = ft_idchar(str[i]);
			if (!identif_checker(str, identif, player) || !identif)
			{
				free(identif);
				return (0);
			}
		}
		if (str[i] == 'F' || str[i] == 'C')
		{
			if (!check_singlid(str, player))
				return (0);
		}
	}
	free(identif);
	return (1);
}
