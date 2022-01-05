/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:54:04 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:54:04 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Iterates the list ’lst’ and applies the function ’f’ to the content of
	each element. Creates a new list resulting of the successive applications
	of the function ’f’. The ’del’ function is used to delete the content
	of an element if needed.
RETURN VALUE
	The new list. NULL if the allocation fails.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_list;

	if (!lst)
		return (NULL);
	new_list = NULL;
	tmp = NULL;
	while (lst)
	{	
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
			ft_lstdelone(tmp, del);
		else
			ft_lstadd_back(&new_list, tmp);
		lst = lst->next;
	}
	return (new_list);
}
