/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdragomi <vdragomi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:48 by vdragomi          #+#    #+#             */
/*   Updated: 2021/12/14 14:52:48 by vdragomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The calloc() function allocates memory for an array of nmemb elements of size
	bytes each and returns a pointer to the allocated memory.  The memory is set
	to zero.  If nmemb or size is 0, then calloc() returns either NULL,or a
	unique pointer value that can later be successfully passed to free().
	If the multiplication of nmemb and size would result in integer overflow,
	then calloc() returns an error. By contrast, an integer overflow would
	not be detected in the following call to malloc(), with the result that
	an incorrectly sized block of memory would be allocated:
		malloc(nmemb * size);

RETURN VALUE
	The calloc() function returns a pointer to the allocated memory, which 
	is suitably aligned for any built-in type. On error, this function return NULL.
	NULL may also be returned by a successful call to calloc() with nmemb or size
	equal to zero.
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*return_p;

	if (nmemb * size > 4294967295)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return_p = malloc (1);
	else
		return_p = malloc (nmemb * size);
	if (return_p == NULL)
		return (NULL);
	ft_memset(return_p, '\0', nmemb * size);
	return (return_p);
}
