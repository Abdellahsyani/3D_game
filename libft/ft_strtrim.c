/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:17:18 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/02 12:41:40 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_chr(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_star(const char *s, const char *d)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!check_chr(d, s[i]))
			return (i);
		i++;
	}
	return (0);
}

static int	ft_end(const char *s2, const char *f)
{
	int	len;

	len = ft_strlen(s2) - 1;
	while (check_chr(f, s2[len]))
	{
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		tl;
	char	*t;
	int		j;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = ft_star(s1, set);
	tl = ft_end(s1, set) - i + 1;
	t = malloc(sizeof(char) *(tl + 1));
	if (!t)
		return (NULL);
	j = 0;
	while (j < tl)
		t[j++] = s1[i++];
	t[j] = '\0';
	return (t);
}
