/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:53:47 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:53:47 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Deletes and frees the given element and every successor of that element,
	using the function ’del’ and free(3). Finally, the pointer to the list
	must be set to NULL.
RETURN VALUE
	None.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = *lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		del(ptr2->content);
		free(ptr2);
	}
	*lst = NULL;
}
