/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:40:41 by mamuller          #+#    #+#             */
/*   Updated: 2021/11/15 20:40:41 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	If c is a lowercase letter, toupper() returns its uppercase equivalent,
	if an uppercase representation exists in the current locale. Otherwise, it
	returns c.
	If c is neither an unsigned char value nor EOF, the behavior of these
	functions is undefined.
RETURN VALUE
	The value returned is that of the converted letter,
	or c if the conversion was not possible.
*/

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	return (c);
}
