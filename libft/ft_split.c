/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:30:13 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/03 16:08:49 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_arr(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free (arr[i]);
	}
	free (arr);
	return (NULL);
}

static int	count_word(char const *str, char c)
{
	int	countw;

	countw = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			countw++;
		while (*str != c && *str)
			str++;
	}
	return (countw);
}

static char	**ft_allocat(char **tab, char const *str, char c)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		count = 0;
		while (str[j + count] && str[count + j] != c)
			count++;
		if (count > 0)
		{
			tab[i] = ft_substr (str, j, count);
			if (!tab[i])
				return (free_arr (tab, i));
			i++;
			j = j + count;
		}
		else
			j++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	cword;

	if (!s)
		return (NULL);
	cword = count_word(s, c);
	arr = (char **)malloc(sizeof(char *) * (cword + 1));
	if (!arr)
		return (NULL);
	return (ft_allocat(arr, s, c));
}
