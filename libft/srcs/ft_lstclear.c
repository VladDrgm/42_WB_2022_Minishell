/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:47:40 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 16:47:40 by dbanfi           ###   ########.fr       */
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
		if (ptr2 != NULL)
		{
			del(ptr2->content);
			free(ptr2);
		}
	}
	*lst = NULL;
}
