/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:39:34 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 20:39:34 by mamuller         ###   ########.fr       */
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
