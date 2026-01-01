/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:13:50 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/01 09:51:52 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if (size != 0 && (count > ((size_t)-1) / size))
		return (NULL);
	p = (char *) malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return ((void *)p);
}
