/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:29:10 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/01 16:07:10 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)src;
	p = (unsigned char *)dst;
	if (dst == src)
	{
		return (dst);
	}
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	return (dst);
}
