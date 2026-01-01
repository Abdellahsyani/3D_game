/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:19:02 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/05 17:39:57 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	b;
	int		i;

	b = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == b)
			return ((char *)s + i);
		i++;
	}
	if (b == '\0')
		return ((char *) s + i);
	return (NULL);
}
