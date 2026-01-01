/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:20:36 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/02 20:32:12 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenum(int n)
{
	int	l;

	l = 0;
	if (n <= 0)
		l = 1;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*p;
	int				i;
	int				len;

	len = ft_lenum(n);
	i = len - 1;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (i >= 0)
	{
		p[i] = (nb % 10) + '0';
		nb /= 10;
		if (i == 0 && n < 0)
			p[i] = '-';
		i--;
	}
	return (p);
}
