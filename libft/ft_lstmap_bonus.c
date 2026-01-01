/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:18:00 by abhimi            #+#    #+#             */
/*   Updated: 2024/11/04 09:52:23 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_frees(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*nl;
	void	*tr;

	if (!lst || !f || !del)
		return (NULL);
	l = NULL;
	while (lst)
	{
		tr = f(lst->content);
		if (!tr)
			return (ft_frees(l, del));
		nl = ft_lstnew(tr);
		if (!nl)
		{
			del(tr);
			return (ft_frees(l, del));
		}
		ft_lstadd_back(&l, nl);
		lst = lst->next;
	}
	return (l);
}
